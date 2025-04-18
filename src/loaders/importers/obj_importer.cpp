// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "loaders/importers/obj_importer.hpp"

#include "engine/geometries/box_geometry.hpp"
#include "engine/materials/phong_material.hpp"
#include "engine/math/vector2.hpp"
#include "engine/math/vector3.hpp"

#include "utilities/logger.hpp"

#include <fstream>
#include <string>
#include <vector>

namespace engine {

namespace {

struct VertexKey {
    int position;
    int uv;
    int normal;

    auto operator<=>(const VertexKey&) const = default;
};

auto ParsePosition(std::istringstream& sstream, const fs::path& path) {
    auto x = 0.0f;
    auto y = 0.0f;
    auto z = 0.0f;
    if (!(sstream >> x >> y >> z)) {
        Logger::Log(LogLevel::Warning, "Malformed position in '{}'", path.string());
        return Vector3::Zero();
    }
    return Vector3 {x, y, z};
}

auto ParseNormal(std::istringstream& sstream, const fs::path& path) {
    auto x = 0.0f;
    auto y = 0.0f;
    auto z = 0.0f;
    if (!(sstream >> x >> y >> z)) {
        Logger::Log(LogLevel::Warning, "Malformed normal in '{}'", path.string());
        return Vector3::Zero();
    }
    return Normalize(Vector3 {x, y, z});
}

auto ParseUVCoordinates(std::istringstream& sstream, const fs::path& path) {
    auto u = 0.0f;
    auto v = 0.0f;
    if (!(sstream >> u >> v)) {
        Logger::Log(LogLevel::Warning, "Malformed UV coordinate in '{}'", path.string());
        return Vector2::Zero();
    }
    return Vector2 {u, v};
}

auto ParseFace(std::istringstream& sstream, const fs::path& path) {
    auto output = std::vector<VertexKey> {};
    auto token = std::string {};

    while (sstream >> token) {
        auto key = VertexKey {-1, -1, -1};
        auto part_stream = std::istringstream {token};
        auto segment = std::string {};

        if (std::getline(part_stream, segment, '/')) {
            if (!segment.empty()) key.position = std::stoi(segment) - 1;
        }
        if (std::getline(part_stream, segment, '/')) {
            if (!segment.empty()) key.uv = std::stoi(segment) - 1;
        }
        if (std::getline(part_stream, segment, '/')) {
            if (!segment.empty()) key.normal = std::stoi(segment) - 1;
        }

        if (key.position == -1) {
            Logger::Log(
                LogLevel::Warning,
                "Face element missing position index in '{}'",
                path.string()
            );
            continue;
        }

        output.push_back(key);
    }

    if (output.size() < 3) {
        Logger::Log(LogLevel::Warning, "Malformed face in '{}'", path.string());
        return std::vector<VertexKey> {};
    }

    return output;
}

} // end unnamed namespace

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
            vertices.emplace_back(ParsePosition(sstream, path));
        } else if (directive == "vn") {
            normals.emplace_back(ParseNormal(sstream, path));
        } else if (directive == "vt") {
            uvs.emplace_back(ParseUVCoordinates(sstream, path));
        } else if (directive == "f") {
            auto face = ParseFace(sstream, path);

        } else {
            Logger::Log(
                LogLevel::Warning,
                "Unknown directive '{}' in file '{}'",
                directive, path.string()
            );
        }
    }

    return BoxGeometry::Create();
}

auto ObjImporter::ParseMaterial(const fs::path& path) -> std::shared_ptr<PhongMaterial> {
    return PhongMaterial::Create(0x049EF4);
}

}