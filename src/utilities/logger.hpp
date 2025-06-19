/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam/core/identity.hpp"
#include "gleam/core/timer.hpp"

#include <filesystem>
#include <format>
#include <iostream>
#include <mutex>
#include <source_location>
#include <string>

namespace gleam {

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
            const auto lock = std::scoped_lock(mutex_);

            auto stream = level == LogLevel::Error ? &std::cerr : &std::cout;
            const auto& path = fs::path{loc.file_name()};
            // std::format needs a compile-time string; std::vformat allows
            // runtime strings using format args.
            const auto message = std::vformat(
                format_str,
                std::make_format_args(static_cast<const Args&>(args)...)
            );

            *stream << std::format(
                "[{}]{}: {} -> {}:{}\n",
                Timer::GetTimestamp(),
                Logger::ToString(level),
                message,
                path.filename().string(),
                loc.line()
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

namespace std {

template <typename T>
struct formatter<T, enable_if_t<std::is_base_of_v<gleam::Identity, T>, char>> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    template <typename FormatContext>
    auto format(const T& obj, FormatContext& ctx) const {
        return obj.Name().empty() ?
            std::format_to(ctx.out(), "[UUID: {}]", obj.UUID()) :
            std::format_to(ctx.out(), "[Name: {}]", obj.Name());
    }
};

}