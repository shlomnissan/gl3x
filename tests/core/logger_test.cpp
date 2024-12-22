// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <utilities/logger.hpp>

#include <string>

using namespace std::string_literals;

#pragma Standard Logger

TEST(Logger, LogInfo) {
    testing::internal::CaptureStdout();
    engine::Logger::Log(engine::LogLevel::Info, "info");
    auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, ::testing::HasSubstr("\x1B[1;34m[Info]\x1B[0m: info"));
}

TEST(Logger, LogWarning) {
    testing::internal::CaptureStdout();
    engine::Logger::Log(engine::LogLevel::Warning, "warning");
    auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, ::testing::HasSubstr("\x1B[1;33m[Warning]\x1B[0m: warning"));
}

TEST(Logger, LogError) {
    testing::internal::CaptureStderr();
    engine::Logger::Log(engine::LogLevel::Error, "error");
    auto output = testing::internal::GetCapturedStderr();

    EXPECT_THAT(output, ::testing::HasSubstr("\x1B[1;31m[Error]\x1B[0m: error"));
}

TEST(Logger, LogDebug) {
    testing::internal::CaptureStdout();
    engine::Logger::Log(engine::LogLevel::Debug, "debug");
    auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, ::testing::HasSubstr("\x1B[1;35m[Debug]\x1B[0m: debug"));
}

#pragma endregion

#pragma String formatting

TEST(Logger, StringFormatting) {
    testing::internal::CaptureStdout();

    auto version = "OpenGL ES 3.2 NVIDIA 560.94 initialized"s;
    engine::Logger::Log(engine::LogLevel::Info, "version {}", version);

    auto output = testing::internal::GetCapturedStdout();
    EXPECT_THAT(output, ::testing::HasSubstr(
        "\x1B[1;34m[Info]\x1B[0m: version OpenGL ES 3.2 NVIDIA 560.94 initialized")
    );
}

#pragma endregion