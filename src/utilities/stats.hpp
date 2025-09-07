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

    auto BeforeRender(unsigned int n_objects) -> void;

    auto AfterRender() -> void;

    auto Draw() -> void;

    ~Stats();

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

}