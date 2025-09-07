/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <memory>

namespace gleam {

class Stats {
public:
    Stats();

    auto BeforeRender() -> void;

    auto AfterRender(unsigned n_objects) -> void;

    auto Draw(float window_width) const -> void;

    ~Stats();

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

}