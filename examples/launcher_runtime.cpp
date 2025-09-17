/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <memory>

#include <gleam/gleam.hpp>

#include "examples.hpp"

using namespace gleam;

class ExamplesApp : public Application {
public:
    auto Configure() -> Application::Parameters override {
        return {
            .title = "Examples (Runtime Initialization)",
            .clear_color = 0x444444,
            .width = 1024,
            .height = 768,
            .antialiasing = 0,
            .vsync = false,
            .show_stats = true
        };
    }

    auto CreateScene() -> std::shared_ptr<Scene> override {
        if (examples_ == nullptr) {
            auto context = GetContext();
            examples_ = std::make_unique<Examples>(
                const_cast<gleam::SharedContext*>(context),
                [this](std::shared_ptr<Scene> scene) { SetScene(scene); }
            );
        }
        return examples_->scene;
    }

    auto CreateCamera() -> std::shared_ptr<Camera> override {
        auto camera = PerspectiveCamera::Create({
            .fov = math::DegToRad(60.0f),
            .aspect = GetContext()->Parameters().aspect_ratio,
            .near = 0.1f,
            .far = 1000.0f
        });
        camera->transform.Translate({0.0f, 0.0f, 3.0f});
        return camera;
    }

    auto Update(float delta) -> bool override {
        examples_->Draw();
        return true;
    }

private:
    std::unique_ptr<Examples> examples_ {nullptr};
};

auto main() -> int {
    auto app = ExamplesApp {};
    app.Start();

    return 0;
}