// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

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
            frames_per_second_.Push(static_cast<float>(time_.frame_count));

            // Frame time is computed once per frame, but we
            // only add a value to the dataset once per second.
            frame_time_.Push(time_.frame_time);

            time_.frame_count = 0;
            time_.last_frame_rate_update = now;
        }

        if (Update(delta)) {
            time_.frame_time = timer.GetElapsedMilliseconds();
            scene->ProcessUpdates(delta);
            renderer->Render(scene.get(), camera.get());
            time_.frame_time = timer.GetElapsedMilliseconds() - time_.frame_time;

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
    ImGui::SetNextWindowSize({window_width, 134.0f});
    ImGui::SetNextWindowPos({params.width - window_width - 10.0f, 10});
    ImGui::Begin("##Stats", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar
    );

    // FPS historgram
    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, {0.68f, 0.07f, 0.35f, 1.0f});
    ImGui::Text("FPS: %.2f", frames_per_second_.LastValue());
    ImGui::PlotHistogram(
        "##FPS",
        frames_per_second_.Buffer(), 150, 0, nullptr, 0.0f, 120.0f, {235, 40}
    );
    ImGui::PopStyleColor();

    // Frame time histogram
    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, {0.40f, 0.70f, 0.20f, 1.0f});
    ImGui::Text("Frame Time: %.2f", frame_time_.LastValue());
    ImGui::PlotHistogram(
        "##Frame Time",
        frame_time_.Buffer(), 150, 0, nullptr, 0.0f, 10.0f, {235, 40}
    );
    ImGui::PopStyleColor();

    ImGui::End();
}

}