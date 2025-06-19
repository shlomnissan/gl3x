/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "renderer/gl/gl_textures.hpp"

#include "gleam/textures/texture_2d.hpp"

#include "utilities/logger.hpp"

namespace gleam {

auto GLTextures::Bind(const std::shared_ptr<Texture>& texture) -> void {
    auto tex_id = texture->renderer_id;
    if (tex_id != 0 && tex_id == current_texture_id_) return;

    if (tex_id == 0) {
        GenerateTexture(texture.get());
        textures_.emplace_back(texture);
    }
}

auto GLTextures::GenerateTexture(Texture* texture) const -> void {
    auto& tex_id = texture->renderer_id;

    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);

    // Currently, the engine only supports 2D textures.
    auto texture_2d = static_cast<Texture2D*>(texture);

    // Use glTexImage2D instead of glTexStorage2D since we target OpenGL 4.1
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        // The engine-specific .tex format guarantees RGBA8 format.
        GL_RGBA8,
        texture_2d->width,
        texture_2d->height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        texture_2d->data.data()
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    if (glGetError() != GL_NO_ERROR) {
        Logger::Log(LogLevel::Error, "OpenGL error failed to generate texture");
    }

    texture->OnDispose([this](Disposable* target) {
        glDeleteTextures(1, &(static_cast<Texture*>(target)->renderer_id));
        Logger::Log(LogLevel::Info, "Texture buffer cleared {}", *static_cast<Texture*>(target));
    });
}

GLTextures::~GLTextures() {
    for (const auto& texture : textures_) {
        if (auto t = texture.lock()) t->Dispose();
    }
}

}