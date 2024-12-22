// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "utilities/logger.hpp"

namespace engine {

namespace fs = std::filesystem;

std::mutex Logger::mutex_;

auto Logger::ToString(LogLevel level) -> std::string {
    using enum LogLevel;
    switch (level) {
        case Error:    return "\033[1;31m[Error]\033[0m";
        case Warning:  return "\033[1;33m[Warning]\033[0m";
        case Info:     return "\033[1;34m[Info]\033[0m";
        case Debug:    return "\033[1;35m[Debug]\033[0m";
        default:       return "Unknown";
    }
}

}