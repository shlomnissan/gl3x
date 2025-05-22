// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "importers/obj_importer.hpp"

#include "engine/core/geometry.hpp"
#include "engine/materials/phong_material.hpp"
#include "engine/math/vector2.hpp"
#include "engine/math/vector3.hpp"
#include "engine/nodes/mesh.hpp"

#include "utilities/logger.hpp"

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace engine {

namespace {

namespace fs = std::filesystem;

enum VertexAttribute {
    None = 0,
    Position = 1 << 0,
    Normal = 1 << 1,
    UV = 1 << 2
};

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

using VertexMap = std::unordered_map<VertexKey, unsigned, decltype(VertexKeyHash)>;

struct GeometryData {
    std::vector<float> vertex_data;
    std::vector<unsigned int> index_data;

    int attributes = VertexAttribute::None;

    auto AddVertex(const Vector3& position) {
        vertices_.push_back(position);
        attributes |= VertexAttribute::Position;
    }

    auto AddNormal(const Vector3& normal) {
        normals_.push_back(normal);
        attributes |= VertexAttribute::Normal;
    }

    auto AddUV(const Vector2& uv) {
        uvs_.push_back(uv);
        attributes |= VertexAttribute::UV;
    }

    auto Stride() {
        auto output = 6; // position + normal
        if (attributes & VertexAttribute::UV) output += 2;
        return output;
    }

    auto ProcessFace(const std::vector<VertexKey> &face) {
        if (face.empty()) return;

        // triangulate the face using a simple fan method
        for (auto i = 1; i + 1 < face.size(); ++i) {
            for (const auto &key : {face[0], face[i], face[i + 1]}) {
                if (seen_vertices_.contains(key)) {
                    index_data.emplace_back(seen_vertices_[key]);
                    continue;
                }

                seen_vertices_[key] = static_cast<unsigned int>(vertex_data.size() / Stride());

                vertex_data.insert(vertex_data.end(), {
                    vertices_[key.position].x,
                    vertices_[key.position].y,
                    vertices_[key.position].z
                });

                if (attributes & VertexAttribute::Normal) {
                    vertex_data.insert(vertex_data.end(), {
                        normals_[key.normal].x,
                        normals_[key.normal].y,
                        normals_[key.normal].z
                    });
                } else {
                    // if no normals are provided, insert a placeholder.
                    // these temporary values will be replaced in post-processing.
                    vertex_data.insert(vertex_data.end(), {0.0f, 0.0f, 0.0f});
                }

                if (attributes & VertexAttribute::UV) {
                    vertex_data.insert(vertex_data.end(), {
                        uvs_[key.uv].x,
                        uvs_[key.uv].y
                    });
                }

                index_data.emplace_back(seen_vertices_[key]);
            }
        }
    }

    auto Get() {
        ProcessData();
        auto output = Geometry::Create(vertex_data, index_data);
        output->SetAttribute({.type = GeometryAttributeType::Position, .item_size = 3});
        output->SetAttribute({.type = GeometryAttributeType::Normal, .item_size = 3});
        if (attributes & VertexAttribute::UV) {
            output->SetAttribute({.type = GeometryAttributeType::UV, .item_size = 2});
        }
        return output;
    }

private:
    std::vector<Vector3> vertices_;
    std::vector<Vector3> normals_;
    std::vector<Vector2> uvs_;
    VertexMap seen_vertices_ {0, VertexKeyHash};

    auto ProcessData() -> void {
        if (!(attributes & VertexAttribute::Normal)) {
            GenerateNormals();
        }
    }

    auto GenerateNormals() -> void {
        constexpr static auto normal_offset = 3;
        auto stride = Stride();

        for (auto i = 0; i < index_data.size(); i += 3) {
            const auto i0 = index_data[i + 0];
            const auto i1 = index_data[i + 1];
            const auto i2 = index_data[i + 2];

            const auto v0 = Vector3 {
                vertex_data[i0 * stride + 0],
                vertex_data[i0 * stride + 1],
                vertex_data[i0 * stride + 2]
            };

            const auto v1 = Vector3 {
                vertex_data[i1 * stride + 0],
                vertex_data[i1 * stride + 1],
                vertex_data[i1 * stride + 2]
            };

            const auto v2 = Vector3 {
                vertex_data[i2 * stride + 0],
                vertex_data[i2 * stride + 1],
                vertex_data[i2 * stride + 2]
            };

            const auto e1 = v1 - v0;
            const auto e2 = v2 - v0;
            const auto normal = Normalize(Cross(e1, e2));

            for (auto idx : {i0, i1, i2}) {
                vertex_data[idx * stride + normal_offset + 0] += normal.x;
                vertex_data[idx * stride + normal_offset + 1] += normal.y;
                vertex_data[idx * stride + normal_offset + 2] += normal.z;
            }
        }

        for (auto i = 0; i < vertex_data.size(); i += stride) {
            auto v = Vector3(
                vertex_data[i + normal_offset + 0],
                vertex_data[i + normal_offset + 1],
                vertex_data[i + normal_offset + 2]
            );

            v.Normalize();
            vertex_data[i + normal_offset + 0] = v.x;
            vertex_data[i + normal_offset + 1] = v.y;
            vertex_data[i + normal_offset + 2] = v.z;
        }
    }
};

auto parse_mtllib(std::istringstream& sstream, const fs::path& path) {
    auto filename = std::string {};
    sstream >> filename;
    auto mttlib_path = path.parent_path() / filename;

    if (!fs::exists(mttlib_path)) {
        Logger::Log(LogLevel::Warning, "Material library '{}' not found", mttlib_path.string());
        return;
    }

    // TODO: implement material library loading
}

auto parse_position(std::istringstream& sstream, const fs::path& path) {
    auto x = 0.0f;
    auto y = 0.0f;
    auto z = 0.0f;
    if (!(sstream >> x >> y >> z)) {
        Logger::Log(LogLevel::Warning, "Malformed position in '{}'", path.string());
        return Vector3::Zero();
    }
    return Vector3 {x, y, z};
}

auto parse_normal(std::istringstream& sstream, const fs::path& path) {
    auto x = 0.0f;
    auto y = 0.0f;
    auto z = 0.0f;
    if (!(sstream >> x >> y >> z)) {
        Logger::Log(LogLevel::Warning, "Malformed normal in '{}'", path.string());
        return Vector3::Zero();
    }
    return Normalize(Vector3 {x, y, z});
}

auto parse_uv_coordinates(std::istringstream& sstream, const fs::path& path) {
    auto u = 0.0f;
    auto v = 0.0f;
    if (!(sstream >> u >> v)) {
        Logger::Log(LogLevel::Warning, "Malformed UV coordinate in '{}'", path.string());
        return Vector2::Zero();
    }
    return Vector2 {u, v};
}

auto parse_face(std::istringstream& sstream, const fs::path& path) {
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

} // unnamed namespace

namespace obj {

auto import_mesh(const fs::path& path) -> std::shared_ptr<Node> {
    auto root = Node::Create();

    auto handle = std::ifstream(path);
    if (!handle.is_open()) {
        Logger::Log(LogLevel::Error, "Failed to open file '{}'", path.string());
        return root;
    }

    auto geometry = GeometryData {};
    auto line = std::string {};
    while (std::getline(handle, line)) {
        auto sstream = std::istringstream {line};
        auto directive = std::string {};
        sstream >> directive;
        if (directive == "#" || directive.empty()) {
            continue; // skip comments and empty lines
        } else if (directive == "mtllib") {
            parse_mtllib(sstream, path);
        } else if (directive == "v") {
            geometry.AddVertex(parse_position(sstream, path));
        } else if (directive == "vn") {
            geometry.AddNormal(parse_normal(sstream, path));
        } else if (directive == "vt") {
            geometry.AddUV(parse_uv_coordinates(sstream, path));
        } else if (directive == "f") {
            if (!(geometry.attributes & VertexAttribute::Position)) {
                Logger::Log(
                    LogLevel::Error,
                    "Face directive without position data in '{}'",
                    path.string()
                );
                return root;
            }
            geometry.ProcessFace(parse_face(sstream, path));
        } else {
            Logger::Log(
                LogLevel::Warning,
                "Unknown directive '{}' in file '{}'",
                directive, path.string()
            );
        }
    }

    root->Add(Mesh::Create(geometry.Get(), PhongMaterial::Create(0x049EF4)));

    return root;
}

} // namespace obj

} // namespace engine