// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/logger.hpp"

#include "engine/core/timer.hpp"

#include <iostream>

namespace engine {

std::mutex Logger::mutex_;

auto Logger::Log(LogLevel level, const fs::path& path, int line, std::string_view message) -> void {
    auto lock = std::scoped_lock(mutex_);
    auto& stream = level == LogLevel::kError ? std::cerr : std::cout;
    stream << fmt::format(
        "[{} -> {}:{}][{}]: {}\n",
        Timer::GetTimestamp(),
        path.filename().string(),
        line,
        Logger::ToString(level),
        message.data()
    );
}

auto Logger::ToString(LogLevel level) -> std::string {
    using enum LogLevel;
    switch (level) {
        case kError:    return "Error";
        case kWarning:  return "Warning";
        case kInfo:     return "Info";
        case kDebug:    return "Debug";
        default:        return "Unknown";
    }
}

}