/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include <chrono>
#include <string>

namespace gleam {

/**
 * @brief A timer class to measure elapsed time.
 */
class GLEAM_EXPORT Timer {
public:
    /**
     * @brief Constructs a new Timer object.
     *
     * @param auto_start Indicates whether the timer should start immediately.
     */
    explicit Timer(bool auto_start);

    /**
     * @brief Starts the timer.
     *
     * If the timer is already running, this function has no effect.
     */
    auto Start() -> void;

    /**
     * @brief Returns the elapsed time in milliseconds.
     *
     * @return double The elapsed time in milliseconds,
     * or 0 if the timer has not been started.
     */
    [[nodiscard]] auto GetElapsedMilliseconds() const -> double;

    /**
     * @brief Returns the elapsed time in seconds.
     *
     * @return double The elapsed time in seconds,
     * or 0 if the timer has not been started.
     */
    [[nodiscard]] auto GetElapsedSeconds() const -> double;

    /**
     * @brief Gets the current timestamp in a formatted string.
     *
     * This function retrieves the current time and formats it as a string
     * in the format "YYYY-MM-DD HH:MM:SS". The time is represented in UTC.
     *
     * @return std::string The current timestamp as a formatted string.
     */
    [[nodiscard]] static auto GetTimestamp() -> std::string;

private:
    /// @brief Indicates whether the timer is currently running.
    bool running_ {false};

    /// @brief Time when the timer was started.
    std::chrono::time_point<std::chrono::steady_clock> start_time_;
};

}