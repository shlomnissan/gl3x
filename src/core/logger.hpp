// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <string>
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
    static auto Log(LogLevel level, std::string_view message) -> void;

private:
    static std::mutex mutex_;

    [[nodiscard]]
    static auto ToString(LogLevel level) -> std::string;
};

}