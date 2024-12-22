// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/core/application_context.hpp"

#include "utilities/logger.hpp"

#include <imgui.h>

namespace engine {

auto ApplicationContext::Setup() -> void {
    InitializeWindow();
    InitializeRenderer();
    initialized_ = true;
}

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
            frames_per_second_.Push(time_.frame_count);
            time_.frame_count = 0;
            time_.last_frame_rate_update = now;
        }

        if (Update(delta)) {
            scene->ProcessUpdates(delta);
            renderer->Render(scene.get(), camera.get());
            if (params.show_stats) {
                RenderStats();
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

auto ApplicationContext::RenderStats() const -> void {
    static const auto window_width = 250.0f;
    ImGui::SetNextWindowSize({window_width, 74.0f});
    ImGui::SetNextWindowPos({params.width - window_width - 10.0f, 10});
    ImGui::Begin("##Stats", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar
    );
    ImGui::Text("FPS: %.2f", frames_per_second_.LastValue());
    ImGui::PlotHistogram(
        "##FPS",
        frames_per_second_.Buffer(), 150, 0, nullptr, 0.0f, 120.0f, {235, 40}
    );
    ImGui::End();
}

}