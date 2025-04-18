// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/loaders/mesh_loader.hpp"

#include "engine/nodes/mesh.hpp"

#include "loaders/importers/obj_importer.hpp"

namespace engine {

auto MeshLoader::ValidFileExtensions() const -> std::vector<std::string> {
    return {".obj"};
}

auto MeshLoader::LoadImpl(const fs::path& path) const -> std::shared_ptr<void> {
    if (path.extension() == ".obj") {
        return ObjImporter::Import(path);
    } else {
        return nullptr;
    }
}

}