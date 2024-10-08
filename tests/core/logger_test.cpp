// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "core/logger.hpp"

#include <string>

using namespace std::string_literals;

#pragma Standard Logger

TEST(Logger, LogInfo) {
    testing::internal::CaptureStdout();
    engine::Logger::Log(engine::LogLevel::Info, "info");
    auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, ::testing::HasSubstr("[Info]: info"));
}

TEST(Logger, LogWarning) {
    testing::internal::CaptureStdout();
    engine::Logger::Log(engine::LogLevel::Warning, "warning");
    auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, ::testing::HasSubstr("[Warning]: warning"));
}

TEST(Logger, LogError) {
    testing::internal::CaptureStderr();
    engine::Logger::Log(engine::LogLevel::Error, "error");
    auto output = testing::internal::GetCapturedStderr();

    EXPECT_THAT(output, ::testing::HasSubstr("[Error]: error"));
}

TEST(Logger, LogDebug) {
    testing::internal::CaptureStdout();
    engine::Logger::Log(engine::LogLevel::Debug, "debug");
    auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, ::testing::HasSubstr("[Debug]: debug"));
}

#pragma endregion

#pragma String formatting

TEST(Logger, StringFormatting) {
    testing::internal::CaptureStdout();

    auto version = "OpenGL ES 3.2 NVIDIA 560.94 initialized"s;
    engine::Logger::Log(engine::LogLevel::Info, "version {}", version);

    auto output = testing::internal::GetCapturedStdout();
    EXPECT_THAT(output, ::testing::HasSubstr(
        "[Info]: version OpenGL ES 3.2 NVIDIA 560.94 initialized")
    );
}

#pragma endregion