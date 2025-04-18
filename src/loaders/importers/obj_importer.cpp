// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "loaders/importers/obj_importer.hpp"

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

const auto VertexKeyHash = [](const VertexKey& key) {
    return std::hash<int>{}(key.position) ^
           std::hash<int>{}(key.uv) ^
           std::hash<int>{}(key.normal);
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

    // Only triangles are supported for now
    if (output.size() != 3) {
        Logger::Log(LogLevel::Warning, "Malformed face in '{}'", path.string());
        return std::vector<VertexKey> {};
    }

    return output;
}

auto Stride(bool has_positions, bool has_normals, bool has_uvs) {
    auto output = 0;
    if (has_positions) output += 3;
    if (has_normals) output += 3;
    if (has_uvs) output += 2;
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

    auto has_positions = false;
    auto has_normals = false;
    auto has_uvs = false;

    auto vertices = std::vector<Vector3> {};
    auto normals = std::vector<Vector3> {};
    auto uvs = std::vector<Vector2> {};
    auto line = std::string {};

    auto vertex_data = std::vector<float> {};
    auto index_data = std::vector<unsigned int> {};
    auto seen_vertices = std::unordered_map<
        VertexKey,
        unsigned int,
        decltype(VertexKeyHash)
    > {0, VertexKeyHash};

    while (std::getline(handle, line)) {
        auto sstream = std::istringstream {line};
        auto directive = std::string {};
        sstream >> directive;

        if (directive == "#") {
            continue; // skip comments
        } else if (directive == "v") {
            vertices.emplace_back(ParsePosition(sstream, path));
            has_positions = true;
        } else if (directive == "vn") {
            normals.emplace_back(ParseNormal(sstream, path));
            has_normals = true;
        } else if (directive == "vt") {
            uvs.emplace_back(ParseUVCoordinates(sstream, path));
            has_uvs = true;
        } else if (directive == "f") {
            if (!has_positions) {
                Logger::Log(
                    LogLevel::Error,
                    "Face directive without position data in '{}'",
                    path.string()
                );
                return Geometry::Create();
            }
            auto face = ParseFace(sstream, path);
            if (face.empty()) continue; // skip malformed faces

            for (const auto& key : face) {
                if (seen_vertices.contains(key)) {
                    index_data.emplace_back(seen_vertices[key]);
                } else {
                    const auto stride = Stride(has_positions, has_normals, has_uvs);
                    seen_vertices[key] = static_cast<unsigned int>(vertex_data.size() / stride);

                    vertex_data.insert(vertex_data.end(), {
                        vertices[key.position].x,
                        vertices[key.position].y,
                        vertices[key.position].z
                    });

                    if (has_normals) {
                        vertex_data.insert(vertex_data.end(), {
                            normals[key.normal].x,
                            normals[key.normal].y,
                            normals[key.normal].z
                        });
                    }

                    if (has_uvs) {
                        vertex_data.insert(vertex_data.end(), {
                            uvs[key.uv].x,
                            uvs[key.uv].y
                        });
                    }

                    index_data.emplace_back(seen_vertices[key]);
                }
            }
        } else {
            Logger::Log(
                LogLevel::Warning,
                "Unknown directive '{}' in file '{}'",
                directive, path.string()
            );
        }
    }

    using enum GeometryAttributeType;
    auto geometry = Geometry::Create(vertex_data, index_data);
    geometry->SetAttribute({.type = Position, .item_size = 3});

    if (has_normals) geometry->SetAttribute({.type = Normal, .item_size = 3});
    if (has_uvs) geometry->SetAttribute({.type = UV, .item_size = 2});

    return geometry;
}

auto ObjImporter::ParseMaterial(const fs::path& path) -> std::shared_ptr<PhongMaterial> {
    return PhongMaterial::Create(0x049EF4);
}

}