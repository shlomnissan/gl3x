/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "vglx/utilities/timer.hpp"

#include "utilities/logger.hpp"

#include <format>

namespace vglx {

using Clock = std::chrono::steady_clock;

Timer::Timer(bool auto_start) {
    if (auto_start) Start();
}

auto Timer::Start() -> void {
    if (running_) {
        Logger::Log(LogLevel::Warning, "The timer is already running");
        return;
    }

    running_ = true;
    start_time_ = Clock::now();
}

auto Timer::GetElapsedMilliseconds() const -> double {
    if (!running_) {
        Logger::Log(LogLevel::Warning, "The timer has not been started");
        return 0.0;
    }

    return static_cast<double>(
        std::chrono::duration_cast<std::chrono::milliseconds>(
            Clock::now() - start_time_
        ).count()
    );
}

auto Timer::GetElapsedSeconds() const -> double {
    if (!running_) {
        Logger::Log(LogLevel::Warning, "The timer has not been started");
        return 0.0;
    }

    return std::chrono::duration_cast<std::chrono::duration<double>>(
        Clock::now() - start_time_
    ).count();
}

auto Timer::GetTimestamp() -> std::string {
    using std::chrono::system_clock;
    auto now = system_clock::now();
    auto in_time_t = system_clock::to_time_t(now);

    std::tm time_info{};
#ifdef _WIN32
    localtime_s(&time_info, &in_time_t);
#else
    localtime_r(&in_time_t, &time_info);
#endif

    return std::format("{:04}-{:02}-{:02} {:02}:{:02}:{:02}",
        time_info.tm_year + 1900,
        time_info.tm_mon + 1,
        time_info.tm_mday,
        time_info.tm_hour,
        time_info.tm_min,
        time_info.tm_sec
    );
}

}