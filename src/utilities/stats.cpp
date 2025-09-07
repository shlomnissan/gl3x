/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "stats.hpp"

#include "gleam/core/timer.hpp"

#include "utilities/data_series.hpp"

namespace gleam {

struct Stats::Impl {

};

Stats::Stats() : impl_(std::make_unique<Stats::Impl>()) {

}

auto Stats::BeforeRender(unsigned int n_objects) -> void {

}

auto Stats::AfterRender() -> void {

}

auto Stats::Draw() -> void {

}

Stats::~Stats() = default;

}