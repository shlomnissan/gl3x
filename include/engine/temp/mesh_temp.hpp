// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <vector>

#include <engine/temp/shader.hpp>

namespace engine {

class MeshTemp {
public:
    MeshTemp(
        const std::vector<float>& vertex_data,
        const std::vector<unsigned int>& index_data = {}
    );
    auto Draw(const Shader& shader) const -> void;

private:
    unsigned int vao_ {0};
    unsigned int vbo_ {0};
    unsigned int ebo_ {0};
    unsigned int indices_size_ {0};

    auto ConfigureVertices(const std::vector<float>& vertex_data) -> void;
    auto ConfigureIndices(const std::vector<unsigned int>& index_data) -> void;
};

}