// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "renderer/gl/gl_textures.hpp"

#include "engine/textures/texture_2d.hpp"

#include "utilities/logger.hpp"

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

    auto texture_2d = dynamic_cast<Texture2D*>(texture);

    // Using glTexImage2D instead of glTexStorage2D, as OpenGL 4.1
    // (the latest supported version on macOS) doesn't support the latter.
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        // We currently use stb_image to load images and set the desired number
        // of channels to four, so the data is always in RGBA format.
        GL_RGBA8,
        texture_2d->Image()->Width(),
        texture_2d->Image()->Height(),
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        texture_2d->Image()->Data()
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    if (glGetError() == GL_NO_ERROR) {
        texture_2d->Image()->Dispose();
    } else {
        Logger::Log(LogLevel::Error, "OpenGL error failed to generate texture");
    }
}

auto GLTextures::TextureCallbacks(Texture* texture) -> void {
    texture->OnDispose([this](Disposable* target) {
        const auto& uuid = static_cast<Texture*>(target)->UUID();
        const auto& state = this->bindings_[uuid];
        glDeleteTextures(1, &state.texture_id);
        this->bindings_.erase(uuid);
    });
}

}