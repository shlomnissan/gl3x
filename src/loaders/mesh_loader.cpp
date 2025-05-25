// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/loaders/mesh_loader.hpp"

#include "engine/core/geometry.hpp"
#include "engine/materials/phong_material.hpp"
#include "engine/nodes/mesh.hpp"
#include "engine/nodes/node.hpp"

#include "asset_builder/include/types.hpp"

#include <fstream>

namespace engine {

auto MeshLoader::LoadImpl(const fs::path& path) const -> std::expected<std::shared_ptr<void>, std::string> {
    auto file = std::ifstream {path, std::ios::binary};
    if (!file) {
        return std::unexpected(std::format("Unable to open file '{}'", path.string()));
    }

    auto header = MeshHeader {};
    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    if (std::memcmp(header.magic, "MES0", 4) != 0) {
        return std::unexpected(std::format("Invalid mesh file '{}'", path.string()));
    }

    if (header.version != 1 || header.header_size != sizeof(MeshHeader)) {
        return std::unexpected(std::format("Unsupported mesh version in file '{}'", path.string()));
    }

    auto root = Node::Create();

    for (auto i = 0; i < header.mesh_count; ++i) {
        auto entry_header = MeshEntryHeader {};
        file.read(reinterpret_cast<char*>(&entry_header), sizeof(entry_header));

        if (entry_header.vertex_count == 0 || entry_header.index_count == 0) {
            return std::unexpected(std::format("Mesh entry {} has zero vertices or indices in file '{}'", i, path.string()));
        }

        auto vertex_data = std::vector<float>(entry_header.vertex_count * entry_header.vertex_stride);
        file.read(reinterpret_cast<char*>(vertex_data.data()), entry_header.vertex_data_size);

        auto index_data = std::vector<unsigned int>(entry_header.index_count);
        file.read(reinterpret_cast<char*>(index_data.data()), entry_header.index_data_size);

        auto geometry = Geometry::Create(std::move(vertex_data), std::move(index_data));
        geometry->SetName(entry_header.name);

        geometry->SetAttribute({.type = GeometryAttributeType::Position, .item_size = 3});
        geometry->SetAttribute({.type = GeometryAttributeType::Normal, .item_size = 3});
        if (entry_header.vertex_flags & VertexAttributeFlags::UVs) {
            geometry->SetAttribute({.type = GeometryAttributeType::UV, .item_size = 2});
        }

        root->Add(Mesh::Create(geometry, PhongMaterial::Create(0x049EF4)));
    }

    return root;
}

}