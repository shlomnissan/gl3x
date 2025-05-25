// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#define TINYOBJLOADER_IMPLEMENTATION

#include "mesh_converter.hpp"
#include "types.hpp"

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
    std::size_t operator()(const VertexKey& key) const {
        return std::hash<int>()(key.pos_idx) ^
               std::hash<int>()(key.norm_idx << 1) ^
               std::hash<int>()(key.uv_idx << 2);
    }
};

using VertexMap = std::unordered_map<VertexKey, unsigned, VertexKeyHash>;

namespace {

auto stride(const tinyobj::attrib_t& attrib) {
    auto stride = 6u; // positions and normals are guaranteed
    if (!attrib.texcoords.empty()) {
        stride += 2;
    }
    return stride;
}

}

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

        // TODO: generate normals if not provided

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

    return {};
}