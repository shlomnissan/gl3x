/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "utilities/logger.hpp"

namespace gl3x {

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