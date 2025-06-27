/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/loaders/mesh_loader.hpp"
#include "gleam/loaders/texture_loader.hpp"

#include "gleam/geometries/geometry.hpp"
#include "gleam/materials/phong_material.hpp"
#include "gleam/math/color.hpp"
#include "gleam/nodes/mesh.hpp"
#include "gleam/nodes/node.hpp"
#include "gleam/textures/texture_2d.hpp"

#include "utilities/file.hpp"

#include "asset_builder/include/types.hpp"

#include <cstring>
#include <fstream>
#include <memory>
#include <span>
#include <string>
#include <unordered_map>
#include <vector>

namespace gleam {

namespace {

auto load_materials(const fs::path& path, uint32_t material_count, std::ifstream& file) {
    auto output = std::vector<std::shared_ptr<Material>> {};
    auto texture_loader = TextureLoader::Create();
    auto textures = std::unordered_map<std::string, std::shared_ptr<Texture2D>> {};

    for (auto i = 0; i < material_count; ++i) {
        auto material_header = MaterialEntryHeader {};
        read_binary(file, material_header);

        auto tex = std::string {material_header.texture};
        if (!tex.empty()) {
            if (!textures.contains(tex)) {
                const auto tex_path = path.parent_path().string() + "/" + tex;
                const auto result = texture_loader->Load(tex_path);
                if (result) textures[tex] = result.value();
            }
        }

        auto mat = PhongMaterial::Create();
        mat->color = Color {material_header.diffuse};
        mat->specular = Color {material_header.specular};
        mat->shininess = material_header.shininess;
        if (textures.contains(tex)) {
            mat->color = 0xFFFFFF;
            mat->texture_map = textures[tex];
        }

        output.emplace_back(mat);
    }

    return output;
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

    if (mesh_header.version != 1 || mesh_header.header_size != sizeof(MeshHeader)) {
        return std::unexpected("Unsupported mesh version in file '" + path_s + "'");
    }

    auto materials = load_materials(path, mesh_header.material_count, file);
    auto root = Node::Create();

    for (auto i = 0; i < mesh_header.mesh_count; ++i) {
        auto geometry_header = MeshEntryHeader {};
        read_binary(file, geometry_header);

        if (geometry_header.vertex_count == 0 || geometry_header.index_count == 0) {
            return std::unexpected("Mesh entry has zero vertices or indices in file '" + path_s + "'");
        }

        auto vertex_data = std::vector<float>(geometry_header.vertex_count * geometry_header.vertex_stride);
        read_binary(file, vertex_data, geometry_header.vertex_data_size);

        auto index_data = std::vector<unsigned int>(geometry_header.index_count);
        read_binary(file, index_data, geometry_header.index_data_size);

        auto geometry = Geometry::Create(vertex_data, index_data);
        geometry->SetName(geometry_header.name);

        geometry->SetAttribute({.type = GeometryAttributeType::Position, .item_size = 3});
        geometry->SetAttribute({.type = GeometryAttributeType::Normal, .item_size = 3});
        if (geometry_header.vertex_flags & VertexAttributeFlags::UVs) {
            geometry->SetAttribute({.type = GeometryAttributeType::UV, .item_size = 2});
        }

        auto mat_index = geometry_header.material_index;
        if (mat_index != -1 && mat_index < materials.size()) {
            root->Add(Mesh::Create(geometry, materials[mat_index]));
        } else {
            root->Add(Mesh::Create(geometry, PhongMaterial::Create()));
        }
    }

    return root;
}

}