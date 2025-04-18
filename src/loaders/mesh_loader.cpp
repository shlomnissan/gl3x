// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/loaders/mesh_loader.hpp"

#include "engine/nodes/mesh.hpp"

#include "engine/geometries/box_geometry.hpp"
#include "engine/materials/flat_material.hpp"

namespace engine {

auto MeshLoader::ValidFileExtensions() const -> std::vector<std::string> {
    return {".obj"};
}

auto MeshLoader::LoadImpl(const fs::path& path) const -> std::shared_ptr<void> {
    const auto geometry = BoxGeometry::Create();
    const auto material = FlatMaterial::Create();
    return Mesh::Create(geometry, material);
}

}