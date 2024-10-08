// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/core/timer.hpp"

#include "core/identity.hpp"

#include <filesystem>
#include <iostream>
#include <mutex>
#include <source_location>
#include <string>

#include <fmt/format.h>

namespace engine {

namespace fs = std::filesystem;

enum class LogLevel {
    Error,
    Warning,
    Info,
    Debug
};

class Logger {
public:
    template <typename... Args>
    struct Log {
        Log(
            LogLevel level,
            std::string_view format_str,
            Args&&... args,
            const std::source_location& loc = std::source_location::current())
        {
            auto lock = std::scoped_lock(mutex_);
            auto& stream = level == LogLevel::Error ? std::cerr : std::cout;
            auto path = fs::path{loc.file_name()};
            auto message = fmt::format(fmt::runtime(format_str), std::forward<Args>(args)...);
            stream << fmt::format(
                "[{} -> {}:{}]{}: {}\n",
                Timer::GetTimestamp(),
                path.filename().string(),
                loc.line(),
                Logger::ToString(level),
                message
            );
        }
    };

    template <typename... Args>
    Log(LogLevel level, std::string_view message, Args&&...) -> Log<Args...>;

private:
    static std::mutex mutex_;

    [[nodiscard]] static auto ToString(LogLevel level) -> std::string;
};

}

namespace fmt {

template <typename T>
struct fmt::formatter<T, std::enable_if_t<std::is_base_of_v<engine::Identity, T>, char>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const T& obj, FormatContext& ctx) {
        return obj.Name().empty() ?
            fmt::format_to(ctx.out(), "[UUID: {}]", obj.UUID()) :
            fmt::format_to(ctx.out(), "[Name: {}]", obj.Name());
    }
};

}