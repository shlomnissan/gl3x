/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam/cameras/camera.hpp"
#include "gleam/math/color.hpp"
#include "gleam/nodes/scene.hpp"

#include <memory>

namespace gleam {

class Renderer {
public:
    struct Parameters {
        int width;
        int height;
    };

    explicit Renderer(const Renderer::Parameters& params);

    auto Render(Scene* scene, Camera* camera) -> void;

    auto SetClearColor(const Color& color) -> void;

    [[nodiscard]] auto RenderedObjectsPerFrame() const -> size_t;

    ~Renderer();

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

}