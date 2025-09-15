/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/core/application.hpp"

#include "gleam/cameras/perspective_camera.hpp"
#include "gleam/core/shared_context.hpp"
#include "gleam/events/window_event.hpp"

#include "core/renderer.hpp"
#include "core/window.hpp"
#include "events/event_dispatcher.hpp"

#include "utilities/logger.hpp"
#include "utilities/stats.hpp"

#include <algorithm>
#include <expected>
#include <string>

namespace gleam {

constexpr auto kMaxDelta = 0.1; // 100ms

namespace {

auto create_default_camera(int width, int height) {
    return PerspectiveCamera::Create({
        .fov = math::DegToRad(60.0f),
        .aspect = static_cast<float>(width) / height,
        .near = 0.1f,
        .far = 1000.0f
    });
}

}

struct Application::Impl {
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Camera> camera;
    std::unique_ptr<Window> window;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<SharedContext> shared_context;
    std::shared_ptr<EventListener> event_listener;

    double last_frame_time = 0.0;

    auto InitializeWindow(const Application::Parameters& params) -> std::expected<void, std::string> {
        window = std::make_unique<Window>(Window::Parameters{
            .title = params.title,
            .width = params.width,
            .height = params.height,
            .antialiasing = params.antialiasing,
            .vsync = params.vsync
        });
        return window->Initialize();
    }

    auto InitializeRenderer(const Application::Parameters& params) -> std::expected<void, std::string> {
        renderer = std::make_unique<Renderer>(Renderer::Parameters {
            .width = window->FramebufferWidth(),
            .height = window->FramebufferHeight(),
            .clear_color = params.clear_color
        });
        return renderer->Initialize();
    }
};

Application::Application() : impl_(std::make_unique<Impl>()) {}

auto Application::Setup() -> void {
    const auto params = Configure();
    show_stats_ = params.show_stats;

    auto init_window_result = impl_->InitializeWindow(params);
    if (!init_window_result) {
        Logger::Log(LogLevel::Error, "{}", init_window_result.error());
        return;
    }

    auto init_renderer_result = impl_->InitializeRenderer(params);
    if (!init_renderer_result) {
        Logger::Log(LogLevel::Error, "{}", init_renderer_result.error());
        return;
    }

    auto window = impl_->window.get();
    auto camera = impl_->camera.get();

    impl_->shared_context = std::make_unique<SharedContext>(SharedContext::SharedParameters {
        .camera = camera,
        .aspect_ratio = window->AspectRatio(),
        .framebuffer_width = window->FramebufferWidth(),
        .framebuffer_height = window->FramebufferHeight(),
        .window_width = window->Width(),
        .window_height = window->Height()
    });

    SetCamera(CreateCamera());
    if (!impl_->camera) {
        SetCamera(create_default_camera(
            GetParameters().window_width,
            GetParameters().window_height
        ));
    }

    SetScene(CreateScene());

    impl_->event_listener = std::make_shared<EventListener>([&](Event* event) {
        if (event->GetType() == EventType::Window) {
            auto e = static_cast<WindowEvent*>(event);

            if (e->type == WindowEvent::Type::FramebufferResize) {
                const auto w = static_cast<int>(e->framebuffer.x);
                const auto h = static_cast<int>(e->framebuffer.y);

                impl_->shared_context->params_.framebuffer_width = w;
                impl_->shared_context->params_.framebuffer_height = h;
                impl_->renderer->SetViewport(0, 0, w, h);
                impl_->camera->Resize(w, h);
            }

            if (e->type == WindowEvent::Type::WindowResize) {
                const auto w = static_cast<int>(e->window.x);
                const auto h = static_cast<int>(e->window.y);

                impl_->shared_context->params_.window_width = w;
                impl_->shared_context->params_.window_height = h;
            }
        }
    });

    EventDispatcher::Get().AddEventListener("window_event", impl_->event_listener);
}

auto Application::Start() -> void {
    Setup();

    timer_.Start();
    impl_->last_frame_time = timer_.GetElapsedSeconds();

    auto stats = Stats {};

    impl_->window->Start([this, &stats]() {
        const auto now = timer_.GetElapsedSeconds();

        // Guard against timer anomalies and giant stalls.
        auto delta_sec = std::clamp(
            now - impl_->last_frame_time, 0.0, kMaxDelta
        );

        impl_->last_frame_time = now;
        const auto delta = static_cast<float>(delta_sec);

        if (!Update(delta)) {
            impl_->window->Break();
            return;
        }

        stats.BeforeRender();
        impl_->scene->ProcessUpdates(delta);
        impl_->renderer->Render(impl_->scene.get(), impl_->camera.get());
        stats.AfterRender(impl_->renderer->RenderedObjectsPerFrame());

        if (show_stats_) {
            stats.Draw(static_cast<float>(GetParameters().window_width));
        }
    });
}

auto Application::GetParameters() const -> SharedContext::SharedParameters {
    return impl_->shared_context->Parameters();
}

auto Application::GetScene() const -> Scene* {
    return impl_->scene.get();
}

auto Application::GetCamera() const -> Camera* {
    return impl_->camera.get();
}

auto Application::SetScene(std::shared_ptr<Scene> scene) -> void {
    impl_->scene = scene;
    impl_->scene->SetContext(impl_->shared_context.get());
}

auto Application::SetCamera(std::shared_ptr<Camera> camera) -> void {
    impl_->shared_context->params_.camera = camera.get();
    impl_->camera = camera;
}

Application::~Application() {
    EventDispatcher::Get().RemoveEventListener("window_event", impl_->event_listener);
}

}