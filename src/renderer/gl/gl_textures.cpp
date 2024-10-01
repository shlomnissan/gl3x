// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "renderer/gl/gl_textures.hpp"

#include "core/logger.hpp"
#include "engine/textures/texture_2d.hpp"

namespace engine {

auto GLTextures::Bind(Texture* texture) -> void {
    GLTextureState state;
    if (bindings_.contains(texture->UUID())) {
        state = bindings_[texture->UUID()];
        if (state.texture_id == current_texture_id_) { return; }
    } else {
        GenerateTexture(texture, state);
        TextureCallbacks(texture);
        bindings_.try_emplace(texture->UUID(), state);
    }
    glBindTexture(GL_TEXTURE_2D, state.texture_id);
    current_texture_id_ = state.texture_id;
}

auto GLTextures::GenerateTexture(Texture* texture, GLTextureState& state) const -> void {
    glGenTextures(1, &state.texture_id);
    glBindTexture(GL_TEXTURE_2D, state.texture_id);

    auto tex = dynamic_cast<Texture2D*>(texture);

    glTexStorage2D(
        GL_TEXTURE_2D,
        1,
        GL_RGB8,
        tex->Image().Width(),
        tex->Image().Height()
    );

    glTexSubImage2D(
        GL_TEXTURE_2D,
        0, 0, 0,
        tex->Image().Width(),
        tex->Image().Height(),
        GL_RGB,
        GL_UNSIGNED_BYTE,
        tex->Image().Data()
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    if (glGetError() == GL_NO_ERROR) {
        tex->Image().Clear();
    } else {
        LogError("OpenGL error failed to generate texture");
    }
}

auto GLTextures::TextureCallbacks(Texture* texture) -> void {
    texture->OnDispose([this](Disposable* target) {
        auto& uuid = static_cast<Texture*>(target)->UUID();
        auto& state = this->bindings_[uuid];
        glDeleteTextures(1, &state.texture_id);
        this->bindings_.erase(uuid);
    });
}

}