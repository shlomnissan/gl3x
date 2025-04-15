// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/core/application_context.hpp"

#include "utilities/logger.hpp"
#include "utilities/performance_graph.hpp"

namespace engine {

ApplicationContext::ApplicationContext() {
    performance_graph_ = std::make_unique<PerformanceGraph>();
}

auto ApplicationContext::Setup() -> void {
    InitializeWindow();
    InitializeRenderer();

    shared_context_ = std::make_unique<SharedContext>(SharedContext::SharedParameters {
        .ratio = window_->AspectRatio(),
        .width = window_->Width(),
        .height = window_->Height(),
        .debug = params.debug
    });
}

auto ApplicationContext::Start() -> void {
    Configure();
    Setup();

    if (shared_context_ == nullptr) {
        Logger::Log(LogLevel::Error,
            "The application context was not initialized properly. "
            "Please ensure that ApplicationContext::Setup has been called, "
            "and check the console logs for any errors."
        );
        return;
    }

    if (!scene_) {
        Logger::Log(LogLevel::Error,
            "You must override the Setup method and assign a Scene object."
        );
        return;
    }

    if (!camera_) {
        Logger::Log(LogLevel::Error,
            "You must override the Setup method and assign a Camera object."
        );
        return;
    }

    timer.Start();

    window_->Start([this]() {
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
            performance_graph_->AddData(RenderedObjects, renderer_->RenderedObjectsPerFrame());
            frame_count = 0;
            last_frame_rate_update = now;
        }

        if (Update(delta)) {
            const auto start_time = timer.GetElapsedMilliseconds();
            scene_->ProcessUpdates(delta);
            renderer_->Render(scene_.get(), camera_.get());
            const auto end_time = timer.GetElapsedMilliseconds();

            frame_time_ms = end_time - start_time;

            if (params.debug) {
                performance_graph_->RenderGraph(static_cast<float>(params.width));
            }
        } else {
            window_->Break();
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
    window_ = std::make_unique<Window>(window_params);
    return window_->HasErrors() ? false : true;
}

auto ApplicationContext::InitializeRenderer() -> bool {
    const auto renderer_params = Renderer::Parameters {
        .width = window_->Width(),
        .height = window_->Height()
    };
    renderer_ = std::make_unique<Renderer>(renderer_params);
    return true;
}

auto ApplicationContext::SetScene(std::shared_ptr<Scene> scene) -> void {
    scene_ = scene;
    scene_->SetContext(shared_context_.get());
}

auto ApplicationContext::SetCamera(std::shared_ptr<Camera> camera) -> void {
    camera_ = camera;
}

auto ApplicationContext::SetTitle(std::string_view title) -> void {
    window_->SetTitle(title);
}

auto ApplicationContext::SetClearColor(const Color& color) -> void {
    renderer_->SetClearColor(color);
}

auto ApplicationContext::Context() const -> const SharedContext* {
    if (shared_context_ == nullptr) {
        Logger::Log(LogLevel::Error,
            "The shared context is not initialized. Ensure that "
            "ApplicationContext::Setup has been called before attempting "
            "to access the shared context."
        );
        return nullptr;
    }
    return shared_context_.get();
}

ApplicationContext::~ApplicationContext() = default;

}