// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include <chrono>
#include <string>

namespace engine {

/**
 * @brief A timer class to measure elapsed time.
 */
class ENGINE_EXPORT Timer {
public:
    /**
     * @brief Starts the timer.
     *
     * If the timer is already running, this function has no effect.
     */
    auto Start() -> void;

    /**
     * @brief Resets the timer.
     *
     * If the timer was running, it will be stopped and reset to zero.
     */
    auto Reset() -> void;

    /**
     * @brief Returns the elapsed time in milliseconds.
     *
     * @return double The elapsed time in milliseconds,
     * or -1 if the timer has not been started.
     */
    [[nodiscard]]
    auto GetElapsedMilliseconds() const -> double;

    /**
     * @brief Returns the elapsed time in seconds.
     *
     * @return double The elapsed time in seconds,
     * or -1 if the timer has not been started.
     */
    [[nodiscard]]
    auto GetElapsedSeconds() const -> double;

    /**
     * @brief Gets the current timestamp in a formatted string.
     *
     * This function retrieves the current time and formats it as a string
     * in the format "YYYY-MM-DD HH:MM:SS". The time is represented in UTC.
     *
     * @return std::string The current timestamp as a formatted string.
     */
    [[nodiscard]] static
    auto GetTimestamp() -> std::string;

private:
    /// @brief Indicates whether the timer has been started.
    bool started_ {false};

    /// @brief Time when the timer was started.
    std::chrono::time_point<std::chrono::steady_clock> start_time_;
};

}