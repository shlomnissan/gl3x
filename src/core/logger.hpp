// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <string>
#include <mutex>
#include <filesystem>

enum class LogLevel {
    kError,
    kWarning,
    kInfo,
    kDebug
};

#define LogError(message) Logger::Log(LogLevel::kError, __FILE__, __LINE__, message)
#define LogWarning(message) Logger::Log(LogLevel::kWarning, __FILE__, __LINE__, message)
#define LogInfo(message) Logger::Log(LogLevel::kInfo, __FILE__, __LINE__, message)
#define LogDebug(message) Logger::Log(LogLevel::kDebug, __FILE__, __LINE__, message)

namespace engine {

namespace fs = std::filesystem;

class Logger {
public:
    static auto Log(LogLevel level, const fs::path& path, int line, std::string_view message) -> void;

private:
    static std::mutex mutex_;

    [[nodiscard]]
    static auto ToString(LogLevel level) -> std::string;
};

}