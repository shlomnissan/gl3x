// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#define TINYOBJLOADER_IMPLEMENTATION

#include "mesh_converter.hpp"
#include "texture_converter.hpp"
#include "types.hpp"

#include <cmath>
#include <format>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "tiny_obj_loader.hpp"

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

auto stride(const tinyobj::attrib_t& attrib) {
    auto stride = 6u; // positions and normals are guaranteed
    if (!attrib.texcoords.empty()) {
        stride += 2;
    }
    return stride;
}

auto generate_normals(
    std::vector<float>& vertex_data,
    std::vector<unsigned>& index_data,
    unsigned int stride
) {
    for (auto i = 0; i < index_data.size(); i += 3) {
        const auto i0 = index_data[i + 0];
        const auto i1 = index_data[i + 1];
        const auto i2 = index_data[i + 2];

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
        const auto normal = cross(e0, e1).Normalize();

        constexpr auto normal_offset = 3;
        for (auto idx : {i0, i1, i2}) {
            vertex_data[idx * stride + normal_offset + 0] += normal.x;
            vertex_data[idx * stride + normal_offset + 1] += normal.y;
            vertex_data[idx * stride + normal_offset + 2] += normal.z;
        }
    }
}

auto parse_materials(
    const std::vector<tinyobj::material_t> &materials,
    std::ofstream& out_stream
) {
    // TODO: parse materials
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

        auto mesh_entry_header = MeshEntryHeader {};
        auto name = shape.name.empty() ? "default:Mesh" : shape.name;
        std::strncpy(mesh_entry_header.name, name.c_str(), sizeof(mesh_entry_header.name) - 1);
        mesh_entry_header.vertex_count = static_cast<uint32_t>(seen_vertices.size());
        mesh_entry_header.index_count = static_cast<uint32_t>(index_data.size());
        mesh_entry_header.vertex_stride = stride(attrib);
        mesh_entry_header.material_index = 0; // TODO: handle materials
        mesh_entry_header.vertex_data_size = static_cast<uint64_t>(vertex_data.size() * sizeof(float));
        mesh_entry_header.index_data_size = static_cast<uint64_t>(index_data.size() * sizeof(unsigned));
        mesh_entry_header.vertex_flags = VertexAttributeFlags::Positions | VertexAttributeFlags::Normals;
        if (!attrib.texcoords.empty()) {
            mesh_entry_header.vertex_flags |= VertexAttributeFlags::UVs;
        }

        out_stream.write(reinterpret_cast<const char*>(&mesh_entry_header), sizeof(mesh_entry_header));
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
            std::unexpected(std::format("Error: Failed to load mesh {}\n", input_path.string())) :
            std::unexpected(std::format("Error: {}\n", reader.Error()));
    }

    if (!reader.Warning().empty()) {
        std::cout << std::format("Warning: {}\n", reader.Warning());
    }

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    auto header = MeshHeader {};
    std::memcpy(header.magic, "MES0", 4);
    header.version = 1;
    header.header_size = sizeof(MeshHeader);
    header.mesh_count = static_cast<uint32_t>(shapes.size());

    auto out_stream = std::ofstream {output_path, std::ios::binary};
    if (!out_stream) {
        return std::unexpected("Failed to open output file: " + output_path.string());
    }

    out_stream.write(reinterpret_cast<const char*>(&header), sizeof(header));

    parse_materials(materials, out_stream);
    parse_shapes(shapes, attrib, out_stream);

    return {};
}