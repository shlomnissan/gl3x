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

/**
 * @brief Enum representing the logging level.
 */
enum class LogLevel {
    Error,      ///< Error logging level.
    Warning,    ///< Warning logging level.
    Info,       ///< Informational logging level.
    Debug       ///< Debug logging level.
};

/**
 * @brief Class responsible for logging messages with various log levels.
 */
class Logger {
public:
    /**
     * @brief Nested structure for handling log entries with variable arguments.
     *
     * @tparam Args Variadic template arguments representing data to format into the log message.
     */
    template <typename... Args>
    struct Log {
        /**
         * @brief Constructs a log entry with specified level, format string, and arguments.
         *
         * @param level The logging level (e.g., Error, Warning, Info, Debug).
         * @param format_str A format string for the log message.
         * @param args Variadic arguments to be formatted into the log message.
         * @param loc The source location where the log was created (default: current source location).
         */
        Log(
            LogLevel level,
            std::string_view format_str,
            Args&&... args,
            const std::source_location& loc = std::source_location::current())
        {
            const auto lock = std::scoped_lock(mutex_);

            auto stream = level == LogLevel::Error ? &std::cerr : &std::cout;
            const auto& path = fs::path{loc.file_name()};
            const auto message = fmt::format(fmt::runtime(format_str), args...);
            *stream << fmt::format(
                "[{}]{}: {} -> {}:{}\n",
                Timer::GetTimestamp(),
                Logger::ToString(level),
                message,
                path.filename().string(),
                loc.line()
            );
        }
    };

    /**
     * @brief Deduction guide for constructing a `Log` instance.
     *
     * @tparam Args Variadic template arguments representing data to format into the log message.
     * @param level The logging level for the log entry.
     * @param message The message format string.
     * @param args Arguments to format into the log message.
     */
    template <typename... Args>
    Log(LogLevel level, std::string_view message, Args&&...) -> Log<Args...>;

private:
    /// @brief Mutex to ensure thread-safe logging.
    static std::mutex mutex_;

    /**
     * @brief Converts a LogLevel to its string representation.
     *
     * @param level The LogLevel to convert.
     * @return std::string The string representation of the specified LogLevel.
     */
    [[nodiscard]] static auto ToString(LogLevel level) -> std::string;
};

}

namespace fmt {

/**
 * @brief Formatter specialization for types derived from engine::Identity.
 *
 * @tparam T The type to format, which must inherit from engine::Identity.
 */
template <typename T>
struct formatter<T, std::enable_if_t<std::is_base_of_v<engine::Identity, T>, char>> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const T& obj, FormatContext& ctx) {
        return obj.Name().empty() ?
            fmt::format_to(ctx.out(), "[UUID: {}]", obj.UUID()) :
            fmt::format_to(ctx.out(), "[Name: {}]", obj.Name());
    }
};

}