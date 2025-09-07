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
    DataSeries<float, 150> fps_series;
    DataSeries<float, 150> frame_time_series;
    DataSeries<float, 150> rendered_objects_series;

    Timer timer {true};

    double last_flush = 0.0;
    double frame_start = 0.0;
    double frame_time = 0.0;

    unsigned frame_count = 0;

    Impl() {
        last_flush = timer.GetElapsedMilliseconds();
    }

    auto Before(unsigned int n_objects) {
        const auto now = timer.GetElapsedMilliseconds();

        while (now - last_flush >= 1000.0) {
            fps_series.Push(static_cast<float>(frame_count));
            frame_time_series.Push(static_cast<float>(frame_time));
            rendered_objects_series.Push(static_cast<float>(n_objects));
            frame_count = 0;
            last_flush += 1000.0;
        }

        frame_start = now;
        ++frame_count;
    }

    auto After() {
        const auto frame_end = timer.GetElapsedMilliseconds();
        frame_time = frame_end - frame_start;
    }
};

Stats::Stats() : impl_(std::make_unique<Stats::Impl>()) {}

auto Stats::BeforeRender(unsigned int n_objects) -> void {
    impl_->Before(n_objects);
}

auto Stats::AfterRender() -> void {
    impl_->After();
}

auto Stats::Draw() -> void {
    // TODO: draw UI
}

Stats::~Stats() = default;

}