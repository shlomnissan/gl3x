// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/loaders/mesh_loader.hpp"

#include "engine/nodes/node.hpp"

#include "importers/obj_importer.hpp"

namespace engine {

auto MeshLoader::LoadImpl(const fs::path& path) const -> std::expected<std::shared_ptr<void>, std::string> {
    if (path.extension() != ".obj") {
        return std::unexpected(std::format("Unsupported file type '{}'", path.extension().string()));
    }

    return obj::import_mesh(path);
}

}