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

    window->Start([this]() {
        static auto last_frame_time = 0.0;
        static auto last_frame_rate_update = 0.0;
        static auto frame_time_ms = 0.0;
        static unsigned int frame_count = 0;

        const auto now = timer.GetElapsedSeconds();
        const auto delta = static_cast<float>(now - last_frame_time);

        last_frame_time = now;
        frame_count++;

        // update the performance graph every second
        if (now - last_frame_rate_update >= 1.0) {
            using enum PerformanceMetric;
            performance_graph_->AddData(FramesPerSecond, frame_count);
            performance_graph_->AddData(FrameTime, frame_time_ms);
            performance_graph_->AddData(RenderedObjects, renderer->RenderedObjectsPerFrame());
            frame_count = 0;
            last_frame_rate_update = now;
        }

        if (Update(delta)) {
            const auto start_time = timer.GetElapsedMilliseconds();
            scene->ProcessUpdates(delta);
            renderer->Render(scene.get(), camera.get());
            const auto end_time = timer.GetElapsedMilliseconds();

            frame_time_ms = end_time - start_time;

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