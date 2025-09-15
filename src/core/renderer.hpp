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
#include <string>

namespace gleam {

class Renderer {
public:
    struct Parameters {
        int width;
        int height;
        Color clear_color;
    };

    explicit Renderer(const Renderer::Parameters& params);

    [[nodiscard]] auto Initialize() -> std::expected<void, std::string>;

    auto Render(Scene* scene, Camera* camera) -> void;

    auto SetViewport(int x, int y, int width, int height) -> void;

    [[nodiscard]] auto RenderedObjectsPerFrame() const -> size_t;

    ~Renderer();

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

}