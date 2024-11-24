// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/core/renderer.hpp"
#include "engine/core/window.hpp"
#include "engine/scene/camera.hpp"
#include "engine/scene/scene.hpp"

#include <memory>

namespace engine {

class ApplicationContext {
public:
    Window::Parameters window_parameters {
        .width = 1024,
        .height = 768,
        .antialiasing = 4,
        .vsync = true
    };

    virtual auto Setup() -> void {
        // No-op. The client should override this function.
    }

    virtual auto Update(float delta) -> bool {
        // No-op. The client should override this function.
        return true;
    }

    auto Start() -> void;

    auto SetScene(std::shared_ptr<Scene> scene) { scene_ = scene; }

    auto SetCamera(std::shared_ptr<Camera> camera) { camera_ = camera; }

    virtual ~ApplicationContext() = default;

private:
    std::unique_ptr<Window> window_ {nullptr};
    std::unique_ptr<Renderer> renderer_ {nullptr};
    std::shared_ptr<Scene> scene_ {nullptr};
    std::shared_ptr<Camera> camera_ {nullptr};

    auto InitializeWindow() -> bool;

    auto InitializeRenderer() -> bool;
};

}