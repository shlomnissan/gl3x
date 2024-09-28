// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "renderer/gl/gl_textures.hpp"

#include "engine/textures/texture_2d.hpp"

namespace engine {

auto GLTextures::Bind(Texture* texture) -> void {
    GLTextureState state;
    if (bindings_.contains(texture->UUID())) {
        state = bindings_[texture->UUID()];
        if (state.texture_id == current_texture_id_) { return; }
    } else {
        glGenTextures(1, &state.texture_id);
        glBindTexture(GL_TEXTURE_2D, state.texture_id);
        GenerateTexture(texture, state);
        TextureCallbacks(texture);
        bindings_.try_emplace(texture->UUID(), state);
    }
    glBindTexture(GL_TEXTURE_2D, state.texture_id);
    current_texture_id_ = state.texture_id;
}

auto GLTextures::GenerateTexture(
    const Texture* texture,
    const GLTextureState& state
) const -> void {
    auto tex = dynamic_cast<const Texture2D*>(texture);

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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

auto GLTextures::TextureCallbacks(Texture* texture) -> void {
    // TODO: implement
}

}