// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <mutex>
#include <source_location>
#include <string>

#include "core/identity.hpp"

#include <fmt/format.h>

namespace engine {

enum class LogLevel {
    Error,
    Warning,
    Info,
    Debug
};

class Logger {
public:
    static auto Log(
        LogLevel level,
        std::string_view message,
        std::source_location loc = std::source_location::current()
    ) -> void;

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