// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "gleam/textures/texture.hpp"

#include <memory>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <glad/glad.h>

namespace gleam {

struct GLTextureState {
    GLuint texture_id {0};
};

class GLTextures {
public:
    GLTextures() = default;

    GLTextures(const GLTextures&) = delete;
    GLTextures(GLTextures&&) = delete;
    GLTextures& operator=(const GLTextures&) = delete;
    GLTextures& operator=(GLTextures&&) = delete;

    auto Bind(const std::shared_ptr<Texture>& texture) -> void;

    ~GLTextures();

private:
    std::unordered_map<std::string_view, GLTextureState> bindings_;

    std::vector<std::weak_ptr<Texture>> textures_;

    GLuint current_texture_id_ {0};

    auto GenerateTexture(Texture* texture, GLTextureState& state) const -> void;

    auto TextureCallbacks(Texture* texture) -> void;
};

}