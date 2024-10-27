// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "core/event_dispatcher.hpp"

#include <memory>

#pragma region Event Listener Management

TEST(EventDispatcher, AddEventListener) {
    auto calls = 0;
    auto listener = std::make_shared<engine::EventListener>(
        [&calls](const engine::Event*) { calls++; }
    );

    engine::EventDispatcher::Get().AddEventListener("TestEvent", listener);
    engine::EventDispatcher::Get().Dispatch("TestEvent", std::make_unique<engine::Event>());

    EXPECT_EQ(calls, 1);
}

TEST(EventDispatcher, RemoveEventListener) {
    auto calls = 0;
    auto listener = std::make_shared<engine::EventListener>(
        [&calls](const engine::Event*) { calls++; }
    );

    engine::EventDispatcher::Get().AddEventListener("TestEvent", listener);
    engine::EventDispatcher::Get().RemoveEventListener("TestEvent", listener);
    engine::EventDispatcher::Get().Dispatch("TestEvent", std::make_unique<engine::Event>());

    EXPECT_EQ(calls, 0);
}

#pragma endregion

#pragma region Event Dispatching

TEST(EventDispatcher, DispatchToSingleListener) {
    auto calls = 0;
    auto listener = std::make_shared<engine::EventListener>(
        [&calls](const engine::Event*) { calls++; }
    );

    engine::EventDispatcher::Get().AddEventListener("TestEvent", listener);
    engine::EventDispatcher::Get().Dispatch("TestEvent", std::make_unique<engine::Event>());

    EXPECT_EQ(calls, 1);
}

TEST(EventDispatcher, DispatchToMultipleListeners) {
    auto calls = 0;

    auto listener_1 = std::make_shared<engine::EventListener>(
        [&calls](const engine::Event*) { calls++; }
    );

    auto listener_2 = std::make_shared<engine::EventListener>(
        [&calls](const engine::Event*) { calls++; }
    );

    engine::EventDispatcher::Get().AddEventListener("TestEvent", listener_1);
    engine::EventDispatcher::Get().AddEventListener("TestEvent", listener_2);
    engine::EventDispatcher::Get().Dispatch("TestEvent", std::make_unique<engine::Event>());

    EXPECT_EQ(calls, 2);
}

#pragma endregion

#pragma region Edge Cases

TEST(EventDispatcher, DispatchNonExistentEvent) {
    testing::internal::CaptureStdout();

    engine::EventDispatcher::Get().Dispatch("NonExistent", std::make_unique<engine::Event>());
    auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, ::testing::HasSubstr("Attempting to dispatch"));
}

TEST(EventDispatcher, DispatchWithExpiredListener) {
    testing::internal::CaptureStdout();

    auto listener = std::make_shared<engine::EventListener>([](const engine::Event*) {});
    engine::EventDispatcher::Get().AddEventListener("TestEvent", listener);
    listener.reset();

    engine::EventDispatcher::Get().Dispatch("TestEvent", std::make_unique<engine::Event>());
    auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, ::testing::HasSubstr("Removed expired"));
}

TEST(EventDispatcher, RemoveNonExistentListener) {
    testing::internal::CaptureStdout();

    auto listener = std::make_shared<engine::EventListener>([](const engine::Event*) {});
    engine::EventDispatcher::Get().RemoveEventListener("NonExistentEvent", listener);
    auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, ::testing::HasSubstr("Attempting to remove"));
}

#pragma endregion