// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <string>
#include <mutex>
#include <filesystem>

#include "core/identity.hpp"

#include <fmt/format.h>

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

namespace fmt {
    template <typename T>
    concept IdentityFormatter = std::is_base_of_v<engine::Identity, T>;

    template <IdentityFormatter T>
    struct formatter<T> {
        constexpr auto parse(const fmt::format_parse_context& ctx) { return ctx.begin(); }

        template <typename FormatContext>
        auto format(const T& obj, FormatContext& ctx) {
            return obj.Name().empty() ?
                fmt::format_to(ctx.out(), "[UUID: {}]", obj.UUID()) :
                fmt::format_to(ctx.out(), "[Name: {}]", obj.Name());
        }
    };
}