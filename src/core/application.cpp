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

#include "utilities/stats.hpp"

#include <algorithm>

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

    auto InitializeWindow(const Application::Parameters& params) -> bool {
        window = std::make_unique<Window>(Window::Parameters{
            .width = params.width,
            .height = params.height,
            .antialiasing = params.antialiasing,
            .vsync = params.vsync
        });

        window->SetTitle(params.title);

        shared_context = std::make_unique<SharedContext>(SharedContext::SharedParameters {
            .ratio = window->AspectRatio(),
            .width = window->Width(),
            .height = window->Height()
        });

        return !window->HasErrors();
    }

    auto InitializeRenderer(const Application::Parameters& params) -> bool {
        renderer = std::make_unique<Renderer>(Renderer::Parameters {
            .width = window->Width(),
            .height = window->Height()
        });
        renderer->SetClearColor(params.clear_color);
        return true;
    }
};

Application::Application() : impl_(std::make_unique<Impl>()) {}

auto Application::Setup() -> void {
    Configure();

    impl_->InitializeWindow(params);
    impl_->InitializeRenderer(params);

    // TODO: verify that window and renderer are initialized properly
    SetCamera(CreateCamera());
    if (!impl_->camera) {
        SetCamera(create_default_camera(params.width, params.height));
    }

    SetScene(CreateScene());

    impl_->event_listener = std::make_shared<EventListener>([&](Event* event) {
        if (event->GetType() == EventType::Window) {
            auto e = static_cast<WindowEvent*>(event);
            impl_->camera->Resize(
                static_cast<int>(e->framebuffer.x),
                static_cast<int>(e->framebuffer.y)
            );
        }
    });

    EventDispatcher::Get().AddEventListener("window_event", impl_->event_listener);
}

auto Application::Start() -> void {
    Setup();

    timer.Start();
    impl_->last_frame_time = timer.GetElapsedSeconds();

    auto stats = Stats {};

    impl_->window->Start([this, &stats]() {
        const auto now = timer.GetElapsedSeconds();

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

        if (params.show_stats) {
            stats.Draw(static_cast<float>(params.width));
        }
    });
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