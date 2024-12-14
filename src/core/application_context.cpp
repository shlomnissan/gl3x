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
            "You must override the Setup method and assign a Scene object."
        );
        return;
    }

    if (!camera) {
        Logger::Log(
            LogLevel::Error,
            "You must override the Setup method and assign a Camera object."
        );
        return;
    }

    timer.Start();

    window->Start([&]() {
        const auto now = timer.GetElapsedSeconds();
        const auto delta = static_cast<float>(now - time_.last_frame_time);
        time_.last_frame_time = now;

        time_.frame_count++;
        if (now - time_.last_frame_rate_update >= 1.0) {
            time_.frames_per_second = time_.frame_count;
            time_.frame_count = 0;
            time_.last_frame_rate_update = now;
            Logger::Log(LogLevel::Info, "FPS: {}", time_.frames_per_second);
        }

        if (Update(delta)) {
            scene->ProcessUpdates(delta);
            renderer->Render(scene.get(), camera.get());
        } else {
            window->Break();
        }
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