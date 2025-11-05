/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "vglx/asset_format.hpp"
#include "vglx/loaders/mesh_loader.hpp"
#include "vglx/loaders/texture_loader.hpp"
#include "vglx/geometries/geometry.hpp"
#include "vglx/materials/phong_material.hpp"
#include "vglx/math/color.hpp"
#include "vglx/nodes/mesh.hpp"
#include "vglx/nodes/node.hpp"
#include "vglx/textures/texture_2d.hpp"

#include "utilities/file.hpp"

#include <cstring>
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace vglx {

namespace {

auto make_phong_from_header(MaterialEntryHeader& h, const std::shared_ptr<Texture2D>& diffuse) {
    auto material = PhongMaterial::Create();
    material->color = Color {h.diffuse};
    material->specular = Color {h.specular};
    material->shininess = h.shininess;

    if (diffuse) {
        material->color = 0xFFFFFF;
        material->albedo_map = diffuse;
    }

    return material;
}

auto configure_geometry_attributes(const MeshEntryHeader& h, const std::shared_ptr<Geometry>& geometry) {
    geometry->SetAttribute({.type = VertexAttributeType::Position, .item_size = 3});
    geometry->SetAttribute({.type = VertexAttributeType::Normal, .item_size = 3});

    if (h.vertex_flags & VertexAttributeFlags::UVs) {
        geometry->SetAttribute({.type = VertexAttributeType::UV, .item_size = 2});
    }
    if (h.vertex_flags & VertexAttributeFlags::Tangents) {
        geometry->SetAttribute({.type = VertexAttributeType::Tangent, .item_size = 4});
    }
    if (h.vertex_flags & VertexAttributeFlags::Colors) {
        geometry->SetAttribute({.type = VertexAttributeType::Color, .item_size = 3});
    }
}

auto load_materials(const fs::path& path, std::ifstream& file, const MeshHeader& mesh_header) {
    auto texture_loader = TextureLoader::Create();
    auto textures = std::unordered_map<std::string, std::shared_ptr<Texture2D>> {};
    auto materials = std::vector<std::shared_ptr<Material>> {};
    materials.reserve(mesh_header.material_count);

    for (auto i = 0; i < mesh_header.material_count; ++i) {
        auto material_header = MaterialEntryHeader {};
        read_binary(file, material_header);

        std::shared_ptr<Texture2D> diffuse_texture;
        auto texture_file = std::string {material_header.texture};
        if (!texture_file.empty()) {
            if (auto it = textures.find(texture_file); it != textures.end()) {
                diffuse_texture = it->second;
            } else {
                const auto texture_path = path.parent_path().string() + "/" + texture_file;
                const auto result = texture_loader->Load(texture_path);
                if (result) {
                    diffuse_texture = result.value();
                    textures.emplace(texture_file, diffuse_texture);
                }
            }
        }
        materials.emplace_back(make_phong_from_header(material_header, diffuse_texture));
    }
    return materials;
}

auto load_mesh(const fs::path& path, std::ifstream& file, const MeshHeader& mesh_header) -> LoaderResult<Node> {
    auto materials = load_materials(path, file, mesh_header);
    auto root = Node::Create();

    for (auto i = 0; i < mesh_header.mesh_count; ++i) {
        auto geometry_header = MeshEntryHeader {};
        read_binary(file, geometry_header);

        if (geometry_header.vertex_count == 0 || geometry_header.index_count == 0) {
            return std::unexpected("Mesh entry has zero vertices or indices");
        }

        auto vertex_data = std::vector<float>(geometry_header.vertex_count * geometry_header.vertex_stride);
        read_binary(file, vertex_data, geometry_header.vertex_data_size);

        auto index_data = std::vector<unsigned int>(geometry_header.index_count);
        read_binary(file, index_data, geometry_header.index_data_size);

        auto geometry = Geometry::Create(vertex_data, index_data);
        geometry->SetName(geometry_header.name);

        configure_geometry_attributes(geometry_header, geometry);

        auto material_idx = geometry_header.material_index;
        if (material_idx < materials.size()) {
            root->Add(Mesh::Create(geometry, materials[material_idx]));
        } else {
            root->Add(Mesh::Create(geometry, PhongMaterial::Create()));
        }
    }

    return root;
}

} // unnamed namespace

auto MeshLoader::LoadImpl(const fs::path& path) const -> LoaderResult<Node> {
    auto file = std::ifstream {path, std::ios::binary};
    auto path_s = path.string();
    if (!file) {
        return std::unexpected("Unable to open file '" + path_s + "'");
    }

    auto mesh_header = MeshHeader {};
    read_binary(file, mesh_header);
    if (std::memcmp(mesh_header.magic, "MES0", 4) != 0) {
        return std::unexpected("Invalid mesh file '" + path_s + "'");
    }

    switch (mesh_header.version) {
        case 1: return load_mesh(path, file, mesh_header);
        default: return std::unexpected("Unsupported mesh version");
    };
}

}