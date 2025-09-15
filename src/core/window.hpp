/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <expected>
#include <functional>
#include <memory>
#include <string>
#include <string_view>

namespace gleam {

class Event;

using OnTickCallback = std::function<void()>;

class Window {
public:
    class Impl;

    struct Parameters {
        std::string title;
        int width;
        int height;
        int antialiasing;
        bool vsync;
    };

    explicit Window(const Window::Parameters& params);

    [[nodiscard]] auto Initialize() -> std::expected<void, std::string>;

    [[nodiscard]] auto FramebufferWidth() const -> int;

    [[nodiscard]] auto FramebufferHeight() const -> int;

    [[nodiscard]] auto Width() const -> int;

    [[nodiscard]] auto Height() const -> int;

    [[nodiscard]] auto AspectRatio() const -> float;

    auto Start(const OnTickCallback& tick) const -> void;

    auto Break() -> void;

    ~Window();

private:
    std::unique_ptr<Impl> impl_;
};

}