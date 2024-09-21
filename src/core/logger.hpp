// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <string_view>
#include <mutex>

namespace engine {

enum class LogLevel {
    kError,
    kWarning,
    kInfo,
    kDebug
};

class Logger {
public:
    static auto Get() -> Logger& {
        static Logger instance;
        return instance;
    }

    Logger(const Logger&) = delete;
    auto operator=(const Logger&) -> Logger& = delete;

    auto Log(LogLevel level, std::string_view message) -> void;

private:
    std::mutex mutex_;

    Logger() = default;

    ~Logger() = default;

    auto ToString(LogLevel level) -> std::string;
};

}