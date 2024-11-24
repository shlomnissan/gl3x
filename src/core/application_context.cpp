// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/core/application_context.hpp"

#include "engine/core/logger.hpp"

namespace engine {

auto ApplicationContext::Start() -> void {
    Configure();
    Setup();

    if (!initialized_) {
        Logger::Log(
            LogLevel::Error,
            "The application context was not initialized properly. "
            "Please ensure that ApplicationContext::Setup has been called, "
            "and check the console logs for any errors."
        );
        return;
    }

    if (!scene) {
        Logger::Log(
            LogLevel::Error,
            "You must override the Setup method and create a Scene object."
        );
        return;
    }

    if (!camera) {
        Logger::Log(
            LogLevel::Error,
            "You must override the Setup method and create a Camera object."
        );
        return;
    }

    window->Start([&](float delta) {
        if (!Update(delta)) {
            window->Break();
        }
        scene->ProcessUpdates(delta);
        renderer->Render(scene.get(), camera.get());
    });
}

auto ApplicationContext::InitializeWindow() -> bool {
    const auto window_params = Window::Parameters {
        .width = params.width,
        .height = params.height,
        .antialiasing = params.antialiasing,
        .vsync = params.vsync
    };
    window = std::make_unique<Window>(window_params);
    return window->HasErrors() ? false : true;
}

auto ApplicationContext::InitializeRenderer() -> bool {
    const auto renderer_params = Renderer::Parameters {
        .width = window->Width(),
        .height = window->Height()
    };
    renderer = std::make_unique<Renderer>(renderer_params);
    return true;
}

}