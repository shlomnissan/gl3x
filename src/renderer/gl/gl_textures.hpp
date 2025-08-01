/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam/textures/texture.hpp"

#include <memory>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <glad/glad.h>

namespace gleam {

enum class GLTextureMapType {
    AlbedoMap = 0,
    AlphaMap = 1
};

class GLTextures {
public:
    GLTextures() = default;

    GLTextures(const GLTextures&) = delete;
    GLTextures(GLTextures&&) = delete;
    GLTextures& operator=(const GLTextures&) = delete;
    GLTextures& operator=(GLTextures&&) = delete;

    auto Bind(
        const std::shared_ptr<Texture>& texture,
        GLTextureMapType map_type
    ) -> void;

    ~GLTextures();

private:
    std::vector<std::weak_ptr<Texture>> textures_;

    GLuint current_texture_id_ {0};

    auto GenerateTexture(Texture* texture) const -> void;
};

}