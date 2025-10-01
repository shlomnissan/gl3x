/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#define TINYOBJLOADER_IMPLEMENTATION

#include "mesh_converter.hpp"
#include "texture_converter.hpp"
#include "types.hpp"

#include <cmath>
#include <filesystem>
#include <print>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "tiny_obj_loader.hpp"

namespace fs = std::filesystem;

struct VertexKey {
    int pos_idx;
    int norm_idx;
    int uv_idx;
    auto operator<=>(const VertexKey&) const = default;
};

struct VertexKeyHash {
    auto operator()(const VertexKey& key) const {
        auto h1 = std::hash<int>{}(key.pos_idx);
        auto h2 = std::hash<int>{}(key.norm_idx);
        auto h3 = std::hash<int>{}(key.uv_idx);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

using VertexMap = std::unordered_map<VertexKey, unsigned, VertexKeyHash>;

namespace {

struct __vec3_t {
    float x;
    float y;
    float z;

    [[nodiscard]] friend auto operator-(const __vec3_t a, const __vec3_t b) {
        return __vec3_t {a.x - b.x, a.y - b.y, a.z - b.z};
    }

    [[nodiscard]] auto Length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    auto Normalize() {
        const auto len = Length();
        if (len != 0.0f) {
            auto m = (1.0f / len);
            x *= m;
            y *= m;
            z *= m;
        }
        return *this;
    }
};

[[nodiscard]] auto cross(const __vec3_t a, const __vec3_t b) {
    return __vec3_t {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

[[nodiscard]] auto dot(const __vec3_t a, const __vec3_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

auto stride(const tinyobj::attrib_t& attrib) {
    auto stride = 6u; // positions and normals are guaranteed
    if (!attrib.colors.empty()) stride += 3;
    if (!attrib.texcoords.empty()) stride += 2;
    return stride;
}

template<size_t N>
auto copy_fixed_size_str(char (&dst)[N], const std::string_view src) {
    std::memset(dst, 0, N);
    std::memcpy(dst, src.data(), std::min(src.size(), N - 1));
}

auto generate_normals(
    std::vector<float>& vertex_data,
    std::vector<unsigned>& index_data,
    unsigned int stride
) {
    constexpr float eps = 1e-6f;
    constexpr auto normal_offset = 3;

    for (auto i = 0; i < index_data.size(); i += 3) {
        auto i1 = index_data[i + 1];
        auto i0 = index_data[i + 0];
        auto i2 = index_data[i + 2];

        auto v0 = __vec3_t {
            vertex_data[i0 * stride + 0],
            vertex_data[i0 * stride + 1],
            vertex_data[i0 * stride + 2]
        };

        auto v1 = __vec3_t {
            vertex_data[i1 * stride + 0],
            vertex_data[i1 * stride + 1],
            vertex_data[i1 * stride + 2],
        };

        auto v2 = __vec3_t {
            vertex_data[i2 * stride + 0],
            vertex_data[i2 * stride + 1],
            vertex_data[i2 * stride + 2],
        };

        auto e0 = v1 - v0;
        auto e1 = v2 - v0;

        auto f = cross(e0, e1);
        if (dot(f, f) <= eps * eps) {
            continue;
        }

        for (auto idx : {i0, i1, i2}) {
            vertex_data[idx * stride + normal_offset + 0] += f.x;
            vertex_data[idx * stride + normal_offset + 1] += f.y;
            vertex_data[idx * stride + normal_offset + 2] += f.z;
        }
    }

    auto vertex_count = vertex_data.size() / stride;
    for (auto i = 0; i < vertex_count; ++i) {
        auto n = __vec3_t {
            vertex_data[i * stride + normal_offset + 0],
            vertex_data[i * stride + normal_offset + 1],
            vertex_data[i * stride + normal_offset + 2]
        };

        if (n.Length() > 0.0f) {
            n.Normalize();
            vertex_data[i * stride + normal_offset + 0] = n.x;
            vertex_data[i * stride + normal_offset + 1] = n.y;
            vertex_data[i * stride + normal_offset + 2] = n.z;
        }
    }
}

auto convert_texture(
    const std::string& texture,
    const fs::path& mesh_input_path
) -> std::string {
    auto tex_path = fs::path {texture};
    auto tex_input = tex_path;

    if (!fs::exists(tex_path)) {
        auto dir = mesh_input_path.parent_path();
        tex_input = dir.append(texture);
        if (!fs::exists(tex_input)) {
            std::println(stderr, "Failed to load texture {}", tex_input.string());
            return "";
        }
    }

    auto tex_output = tex_input;
    tex_output.replace_extension(".tex");
    if (auto result = ::convert_texture(tex_input, tex_output); !result) {
        std::println(stderr, "{}", result.error());
        return "";
    }

    std::println("Generated texture {}", tex_output.string());
    return tex_path.replace_extension(".tex").string();
}

auto parse_materials(
    const std::vector<tinyobj::material_t> &materials,
    const fs::path& mesh_input_path,
    std::ofstream& out_stream
) {
    for (const auto& material : materials) {
        auto mat_entry = MaterialEntryHeader {};

        if (!material.diffuse_texname.empty()) {
            copy_fixed_size_str(
                mat_entry.texture,
                convert_texture(material.diffuse_texname, mesh_input_path)
            );
        }

        copy_fixed_size_str(
            mat_entry.name,
            material.name.empty() ? "default:Material" : material.name
        );

        std::memcpy(mat_entry.ambient, material.ambient, sizeof(material.ambient));
        std::memcpy(mat_entry.diffuse, material.diffuse, sizeof(material.diffuse));
        std::memcpy(mat_entry.specular, material.specular, sizeof(material.specular));
        mat_entry.shininess = material.shininess;

        out_stream.write(reinterpret_cast<const char*>(&mat_entry), sizeof(mat_entry));
    }
}

auto parse_shapes(
    const std::vector<tinyobj::shape_t> &shapes,
    const tinyobj::attrib_t &attrib,
    std::ofstream& out_stream
) {
    for (const auto& shape : shapes) {
        auto& mesh = shape.mesh;
        auto seen_vertices = VertexMap {};
        auto vertex_data = std::vector<float> {};
        auto index_data = std::vector<unsigned> {};

        for (auto i = 0u; i < mesh.indices.size(); ++i) {
            const auto idx = mesh.indices[i];
            VertexKey key = {idx.vertex_index, idx.normal_index, idx.texcoord_index};

            if (seen_vertices.contains(key)) {
                index_data.push_back(seen_vertices[key]);
                continue;
            }

            seen_vertices[key] = static_cast<unsigned>(vertex_data.size() / stride(attrib));
            index_data.push_back(seen_vertices[key]);

            vertex_data.insert(vertex_data.end(), {
                attrib.vertices[3 * idx.vertex_index + 0],
                attrib.vertices[3 * idx.vertex_index + 1],
                attrib.vertices[3 * idx.vertex_index + 2]
            });

            if (idx.normal_index >= 0) {
                vertex_data.insert(vertex_data.end(), {
                    attrib.normals[3 * idx.normal_index + 0],
                    attrib.normals[3 * idx.normal_index + 1],
                    attrib.normals[3 * idx.normal_index + 2]
                });
            } else {
                // if no normals are provided, insert a placeholder.
                // these temporary values will be replaced in post-processing.
                vertex_data.insert(vertex_data.end(), {0.0f, 0.0f, 0.0f});
            }

            if (attrib.colors.size()) {
                vertex_data.insert(vertex_data.end(), {
                    attrib.colors[3 * idx.vertex_index + 0],
                    attrib.colors[3 * idx.vertex_index + 1],
                    attrib.colors[3 * idx.vertex_index + 2]
                });
            }

            if (idx.texcoord_index >= 0) {
                vertex_data.insert(vertex_data.end(), {
                    attrib.texcoords[2 * idx.texcoord_index + 0],
                    attrib.texcoords[2 * idx.texcoord_index + 1]
                });
            }
        }

        if (attrib.normals.empty()) {
            generate_normals(vertex_data, index_data, stride(attrib));
        }

        auto msh_entry = MeshEntryHeader {};

        copy_fixed_size_str(
            msh_entry.name,
            shape.name.empty() ? "default:Mesh" : shape.name
        );

        msh_entry.vertex_count = static_cast<uint32_t>(seen_vertices.size());
        msh_entry.index_count = static_cast<uint32_t>(index_data.size());
        msh_entry.vertex_stride = stride(attrib);
        msh_entry.material_index = mesh.material_ids.front();
        msh_entry.vertex_data_size = static_cast<uint64_t>(vertex_data.size() * sizeof(float));
        msh_entry.index_data_size = static_cast<uint64_t>(index_data.size() * sizeof(unsigned));
        msh_entry.vertex_flags = VertexAttributeFlags::Positions | VertexAttributeFlags::Normals;

        if (!attrib.colors.empty()) msh_entry.vertex_flags |= VertexAttributeFlags::Colors;
        if (!attrib.texcoords.empty()) msh_entry.vertex_flags |= VertexAttributeFlags::UVs;

        out_stream.write(reinterpret_cast<const char*>(&msh_entry), sizeof(msh_entry));
        out_stream.write(reinterpret_cast<const char*>(vertex_data.data()), vertex_data.size() * sizeof(float));
        out_stream.write(reinterpret_cast<const char*>(index_data.data()), index_data.size() * sizeof(unsigned));
    }
}

} // unnamed namespace

auto convert_mesh(
    const fs::path& input_path,
    const fs::path& output_path
) -> std::expected<void, std::string> {
    auto reader_config = tinyobj::ObjReaderConfig {};
    auto reader = tinyobj::ObjReader {};

    if (!reader.ParseFromFile(input_path.string(), reader_config)) {
        return reader.Error().empty() ?
            std::unexpected("Error: Failed to load mesh " + input_path.string() + '\n') :
            std::unexpected("Error " + reader.Error());
    }

    if (!reader.Warning().empty()) {
        std::println("Warning: {}", reader.Warning());
    }

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    auto header = MeshHeader {};
    std::memcpy(header.magic, "MES0", 4);
    header.version = 1;
    header.header_size = sizeof(MeshHeader);
    header.material_count = static_cast<uint32_t>(materials.size());
    header.mesh_count = static_cast<uint32_t>(shapes.size());

    auto out_stream = std::ofstream {output_path, std::ios::binary};
    if (!out_stream) {
        return std::unexpected("Failed to open output file: " + output_path.string());
    }

    out_stream.write(reinterpret_cast<const char*>(&header), sizeof(header));

    parse_materials(materials, input_path, out_stream);
    parse_shapes(shapes, attrib, out_stream);

    return {};
}