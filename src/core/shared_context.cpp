/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/core/shared_context.hpp"

#include "core/window.hpp"

namespace gleam {

auto SharedContext::Create(Window* window, Camera* camera) -> std::unique_ptr<SharedContext> {
    return std::make_unique<SharedContext>(SharedContext::SharedParameters {
        .camera = camera,
        .aspect_ratio = window->AspectRatio(),
        .framebuffer_width = window->FramebufferWidth(),
        .framebuffer_height = window->FramebufferHeight(),
        .window_width = window->Width(),
        .window_height = window->Height()
    });
}

}