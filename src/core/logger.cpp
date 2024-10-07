// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/logger.hpp"

#include "engine/core/timer.hpp"

#include <iostream>
#include <filesystem>

namespace engine {

namespace fs = std::filesystem;

std::mutex Logger::mutex_;

auto Logger::Log(LogLevel level, std::string_view message, std::source_location loc) -> void {
    auto lock = std::scoped_lock(mutex_);
    auto& stream = level == LogLevel::Error ? std::cerr : std::cout;
    auto path = fs::path {loc.file_name()};
    stream << fmt::format(
        "[{} -> {}:{}][{}]: {}\n",
        Timer::GetTimestamp(),
        path.filename().string(),
        loc.line(),
        Logger::ToString(level),
        message.data()
    );
}

auto Logger::ToString(LogLevel level) -> std::string {
    using enum LogLevel;
    switch (level) {
        case Error:    return "Error";
        case Warning:  return "Warning";
        case Info:     return "Info";
        case Debug:    return "Debug";
        default:       return "Unknown";
    }
}

}