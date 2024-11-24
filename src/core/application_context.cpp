// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/core/application_context.hpp"

#include "engine/core/logger.hpp"

/*
TODOs:
- Add doxygen comments
- Make scene and camera public
- Add ApplicationContextParamaters
- Create a configure step
- Create a separate paramaters object for the window
- Create accessors for the window, renderer, scene, and camera
- Improve error messages
- Break the loop if the update function returns false
*/

namespace engine {

auto ApplicationContext::Start() -> void {
    Setup();

    if (!scene_) {
        Logger::Log(LogLevel::Error, "Scene is not set.");
        return;
    }

    if (!camera_) {
        Logger::Log(LogLevel::Error, "Camera is not set.");
        return;
    }

    if (!InitializeWindow() || !InitializeRenderer()) {
        return;
    }

    window_->Start([&](float delta) {
        if (!Update(delta)) {
            // TODO: exit game loop
        }
        scene_->ProcessUpdates(delta);
        renderer_->Render(scene_.get(), camera_.get());
    });
}

auto ApplicationContext::InitializeWindow() -> bool {
    window_ = std::make_unique<Window>(window_parameters);
    return window_->HasErrors() ? false : true;
}

auto ApplicationContext::InitializeRenderer() -> bool {
    const auto params = Renderer::Parameters {
        .width = window_->Width(),
        .height = window_->Height()
    };
    renderer_ = std::make_unique<Renderer>(params);
    return true;
}

}