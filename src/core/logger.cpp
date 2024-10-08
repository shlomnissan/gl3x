// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/logger.hpp"

namespace engine {

namespace fs = std::filesystem;

std::mutex Logger::mutex_;

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