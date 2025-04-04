// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "utilities/data_series.hpp"

namespace engine {

enum class PerformanceMetric {
    FrameTime,
    FramesPerSecond,
    RenderedObjects
};

class PerformanceGraph {
public:
    template <std::convertible_to<float> T>
    auto AddData(PerformanceMetric metric, T value) {
        using enum PerformanceMetric;
        switch (metric) {
        case FrameTime:
            frame_time_.Push(static_cast<float>(value));
            break;
        case FramesPerSecond:
            frames_per_second_.Push(static_cast<float>(value));
            break;
        case RenderedObjects:
            rendered_objects_.Push(static_cast<float>(value));
            break;
        }
    }

    auto RenderGraph(const float viewport_width) const -> void;

private:
    DataSeries<float, 150> frame_time_;
    DataSeries<float, 150> frames_per_second_;
    DataSeries<float, 150> rendered_objects_;
};

}