// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "loaders/importers/obj_importer.hpp"

#include "engine/geometries/box_geometry.hpp"
#include "engine/materials/phong_material.hpp"

namespace engine {

auto ObjImporter::Import(const fs::path& path) -> std::shared_ptr<Mesh> {
    auto geometry = ObjImporter::ParseGeometry(path);
    auto material = ObjImporter::ParseMaterial(path);
    return Mesh::Create(geometry, material);
}

auto ObjImporter::ParseGeometry(const fs::path& path) -> std::shared_ptr<Geometry> {
    return BoxGeometry::Create();
}

auto ObjImporter::ParseMaterial(const fs::path& path) -> std::shared_ptr<PhongMaterial> {
    return PhongMaterial::Create(0x049EF4);
}

}