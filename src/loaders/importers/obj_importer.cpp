// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "loaders/importers/obj_importer.hpp"

#include "engine/geometries/box_geometry.hpp"
#include "engine/materials/phong_material.hpp"
#include "engine/math/vector2.hpp"
#include "engine/math/vector3.hpp"

#include "utilities/logger.hpp"

#include <vector>
#include <string>
#include <fstream>

namespace engine {

namespace {

auto ParseVector3(std::istringstream& sstream, const fs::path& path) {
    auto x = 0.0f;
    auto y = 0.0f;
    auto z = 0.0f;
    if (!(sstream >> x >> y >> z)) {
        Logger::Log(LogLevel::Warning, "Malformed vector in '{}'", path.string());
        return Vector3::Zero();
    }
    return Vector3 {x, y, z};
}

auto ParseVector2(std::istringstream& sstream, const fs::path& path) {
    auto u = 0.0f;
    auto v = 0.0f;
    if (!(sstream >> u >> v)) {
        Logger::Log(LogLevel::Warning, "Malformed vector in '{}'", path.string());
        return Vector2::Zero();
    }
    return Vector2 {u, v};
}

}

auto ObjImporter::Import(const fs::path& path) -> std::shared_ptr<Mesh> {
    auto geometry = ObjImporter::ParseGeometry(path);
    auto material = ObjImporter::ParseMaterial(path);
    return Mesh::Create(geometry, material);
}

auto ObjImporter::ParseGeometry(const fs::path& path) -> std::shared_ptr<Geometry> {
    auto handle = std::ifstream(path);
    if (!handle.is_open()) {
        Logger::Log(LogLevel::Error, "Failed to open file '{}'", path.string());
        return Geometry::Create();
    }

    auto vertices = std::vector<Vector3> {};
    auto normals = std::vector<Vector3> {};
    auto uvs = std::vector<Vector2> {};
    auto line = std::string {};

    while (std::getline(handle, line)) {
        auto sstream = std::istringstream {line};
        auto directive = std::string {};
        sstream >> directive;

        if (directive == "#") {
            continue; // skip comments
        } else if (directive == "v") {
            vertices.emplace_back(ParseVector3(sstream, path));
        } else if (directive == "vn") {
            normals.emplace_back(Normalize(ParseVector3(sstream, path)));
        } else if (directive == "vt") {
            uvs.emplace_back(ParseVector2(sstream, path));
        } else if (directive == "f") {
            // TODO: implement face parsing
        } else {
            Logger::Log(LogLevel::Warning, "Unknown directive '{}' in file '{}'", directive, path.string());
        }
    }

    return BoxGeometry::Create();
}

auto ObjImporter::ParseMaterial(const fs::path& path) -> std::shared_ptr<PhongMaterial> {
    return PhongMaterial::Create(0x049EF4);
}

}