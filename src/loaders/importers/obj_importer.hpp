// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine/nodes/mesh.hpp"
#include "engine/core/geometry.hpp"
#include "engine/materials/phong_material.hpp"

#include <filesystem>

namespace engine {

namespace fs = std::filesystem;

class ObjImporter {
public:
    static auto Import(const fs::path& path) -> std::shared_ptr<Mesh>;

private:
    static auto ParseGeometry(const fs::path& path) -> std::shared_ptr<Geometry>;
    static auto ParseMaterial(const fs::path& path) -> std::shared_ptr<PhongMaterial>;
};

}