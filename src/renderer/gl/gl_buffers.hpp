/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam/geometries/geometry.hpp"
#include "gleam/nodes/instanced_mesh.hpp"

#include <array>
#include <memory>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <glad/glad.h>

namespace gleam {

class GLBuffers {
public:
    GLBuffers() = default;

    GLBuffers(const GLBuffers&) = delete;
    GLBuffers(GLBuffers&&) = delete;
    GLBuffers& operator=(const GLBuffers&) = delete;
    GLBuffers& operator=(GLBuffers&&) = delete;

    auto Bind(const std::shared_ptr<Geometry>& geometry) -> void;

    auto BindInstancedMesh(InstancedMesh* mesh) -> void;

    ~GLBuffers();

private:
    std::unordered_map<GLuint, std::array<GLuint, 4>> bindings_;

    std::vector<std::weak_ptr<Geometry>> geometries_;

    GLuint current_vao_ {0};

    auto GenerateBuffers(Geometry* geometry) -> void;
};

}