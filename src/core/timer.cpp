// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/core/timer.hpp>

namespace engine {
    using Clock = std::chrono::steady_clock;

    auto Timer::Start() -> void {
        started_ = true;
        Reset();
    }

    auto Timer::Reset() -> void {
        start_time_ = Clock::now();
    }

    auto Timer::GetElapsedMilliseconds() const -> double {
        if (!started_) return -1.0;

        return static_cast<double>(
            std::chrono::duration_cast<std::chrono::milliseconds>(
                Clock::now() - start_time_
            ).count()
        );
    }

    auto Timer::GetElapsedSeconds() const -> double {
        if (!started_) return -1.0;

        return std::chrono::duration_cast<std::chrono::duration<double>>(
            Clock::now() - start_time_
        ).count();
    }
}