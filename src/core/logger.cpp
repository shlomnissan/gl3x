// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/logger.hpp"

#include <iostream>

#include <fmt/format.h>

namespace engine {

auto Logger::Log(LogLevel level, std::string_view message) -> void {
    // TODO: add mutex

    auto& stream = level == LogLevel::kError ? std::cerr : std::cout;
    stream << fmt::format(
        "[{}]: {}",
        Logger::ToString(level),
        message.data()
    );
}

auto Logger::ToString(LogLevel level) -> std::string {
    switch (level) {
        case LogLevel::kError:      return "Error";
        case LogLevel::kWarning:    return "Warning";
        case LogLevel::kInfo:       return "Info";
        case LogLevel::kDebug:      return "Debug";
        default:                    return "Unknown";
    }
}

}