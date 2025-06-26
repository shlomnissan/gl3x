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
 * @brief Utility class for measuring elapsed time.
 *
 * The `Timer` class provides a simple mechanism for tracking time intervals
 * using a steady clock. Typical usage includes measuring frame time, profiling
 * sections of code, or retrieving a human-readable timestamp string.
 *
 * @ingroup CoreGroup
 */
class GLEAM_EXPORT Timer {
public:
    /**
     * @brief Constructs a Timer object.
     *
     * @param auto_start If true, the timer starts immediately upon construction.
     */
    explicit Timer(bool auto_start);

    /**
     * @brief Starts the timer.
     */
    auto Start() -> void;

    /**
     * @brief Returns the elapsed time in milliseconds since the timer started.
     *
     * @return double
     */
    [[nodiscard]] auto GetElapsedMilliseconds() const -> double;

    /**
     * @brief Returns the elapsed time in seconds since the timer started.
     *
     * @return double
     */
    [[nodiscard]] auto GetElapsedSeconds() const -> double;

    /**
     * @brief Returns the current local time as a formatted string.
     *
     * The result is formatted as `YYYY-MM-DD HH:MM:SS` using the system's
     * local timezone.
     *
     * @return Formatted string representing the current local time.
     */
    [[nodiscard]] static auto GetTimestamp() -> std::string;

private:
    /// @brief Whether the timer is currently running.
    bool running_ {false};

    /// @brief Start time of the timer.
    std::chrono::time_point<std::chrono::steady_clock> start_time_;
};

}