// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/core/application_context.hpp"

#include "utilities/logger.hpp"
#include "utilities/performance_graph.hpp"

#include <vector>

namespace engine {

ApplicationContext::ApplicationContext() {
    performance_graph_ = std::make_unique<PerformanceGraph>();
}

auto ApplicationContext::Setup() -> void {
    InitializeWindow();
    InitializeRenderer();
    initialized_ = true;
}

auto ApplicationContext::Start() -> void {
    Configure();
    Setup();

    if (!initialized_) {
        Logger::Log(LogLevel::Error,
            "The application context was not initialized properly. "
            "Please ensure that ApplicationContext::Setup has been called, "
            "and check the console logs for any errors."
        );
        return;
    }

    if (!scene) {
        Logger::Log(LogLevel::Error,
            "You must override the Setup method and assign a Scene object."
        );
        return;
    }

    if (!camera) {
        Logger::Log(LogLevel::Error,
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

        using enum PerformanceMetric;

        if (now - time_.last_frame_rate_update >= 1.0) {
            performance_graph_->AddData(FramesPerSecond, time_.frame_count);
            performance_graph_->AddData(FrameTime, time_.frame_time);
            performance_graph_->AddData(RenderedObjects, renderer->RenderedObjectsPerFrame());

            time_.frame_count = 0;
            time_.last_frame_rate_update = now;
        }

        if (Update(delta)) {
            time_.frame_time = timer.GetElapsedMilliseconds();
            scene->ProcessUpdates(delta);
            renderer->Render(scene.get(), camera.get());
            time_.frame_time = timer.GetElapsedMilliseconds() - time_.frame_time;

            if (params.debug) {
                performance_graph_->RenderGraph(static_cast<float>(params.width));
            }
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

ApplicationContext::~ApplicationContext() = default;

}