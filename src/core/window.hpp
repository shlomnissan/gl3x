/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

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
        int width;
        int height;
        int antialiasing;
        bool vsync;
    };

    explicit Window(const Window::Parameters& params);

    ~Window();

    [[nodiscard]] auto Width() const -> int;

    [[nodiscard]] auto Height() const -> int;

    [[nodiscard]] auto AspectRatio() const -> float;

    auto Start(const OnTickCallback& tick) const -> void;

    auto Break() -> void;

    auto SetTitle(std::string_view title) -> void;

    auto HasErrors() const -> bool;

private:
    std::unique_ptr<Impl> impl_;
};

}