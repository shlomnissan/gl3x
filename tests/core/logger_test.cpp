// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "core/logger.hpp"

#pragma Standard Logger

TEST(LoggerTest, LogInfo) {
    testing::internal::CaptureStdout();
    engine::Logger::Get().Log(engine::LogLevel::kInfo, "info");
    auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, ::testing::HasSubstr("[Info]: info"));
}

TEST(LoggerTest, LogWarning) {
    testing::internal::CaptureStdout();
    engine::Logger::Get().Log(engine::LogLevel::kWarning, "warning");
    auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, ::testing::HasSubstr("[Warning]: warning"));
}

TEST(LoggerTest, LogError) {
    testing::internal::CaptureStderr();
    engine::Logger::Get().Log(engine::LogLevel::kError, "error");
    auto output = testing::internal::GetCapturedStderr();

    EXPECT_THAT(output, ::testing::HasSubstr("[Error]: error"));
}

TEST(LoggerTest, LogDebug) {
    testing::internal::CaptureStdout();
    engine::Logger::Get().Log(engine::LogLevel::kDebug, "debug");
    auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, ::testing::HasSubstr("[Debug]: debug"));
}

#pragma endregion