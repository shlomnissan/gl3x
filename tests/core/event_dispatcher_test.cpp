// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "core/event_dispatcher.hpp"

#include <memory>
#include <string>

class EventDispatcherTest : public ::testing::Test {
protected:
    void TearDown() override {
        engine::EventDispatcher::Get().RemoveEventListenersForEvent(testEvent);
    }

    std::string testEvent {"TestEvent"};
};

#pragma region Event Listener Management

TEST_F(EventDispatcherTest, AddEventListener) {
    auto calls = 0;
    auto listener = std::make_shared<engine::EventListener>(
        [&calls](const engine::Event*) { calls++; }
    );

    engine::EventDispatcher::Get().AddEventListener(testEvent, listener);
    engine::EventDispatcher::Get().Dispatch(testEvent, std::make_unique<engine::Event>());

    EXPECT_EQ(calls, 1);
}

TEST_F(EventDispatcherTest, RemoveEventListener) {
    auto calls = 0;
    auto listener = std::make_shared<engine::EventListener>(
        [&calls](const engine::Event*) { calls++; }
    );

    engine::EventDispatcher::Get().AddEventListener(testEvent, listener);
    engine::EventDispatcher::Get().RemoveEventListener(testEvent, listener);
    engine::EventDispatcher::Get().Dispatch(testEvent, std::make_unique<engine::Event>());

    EXPECT_EQ(calls, 0);
}

#pragma endregion

#pragma region Event Dispatching

TEST_F(EventDispatcherTest, DispatchToSingleListener) {
    auto calls = 0;
    auto listener = std::make_shared<engine::EventListener>(
        [&calls](const engine::Event*) { calls++; }
    );

    engine::EventDispatcher::Get().AddEventListener(testEvent, listener);
    engine::EventDispatcher::Get().Dispatch(testEvent, std::make_unique<engine::Event>());

    EXPECT_EQ(calls, 1);
}

TEST_F(EventDispatcherTest, DispatchToMultipleListeners) {
    auto calls = 0;

    auto listener_1 = std::make_shared<engine::EventListener>(
        [&calls](const engine::Event*) { calls++; }
    );

    auto listener_2 = std::make_shared<engine::EventListener>(
        [&calls](const engine::Event*) { calls++; }
    );

    engine::EventDispatcher::Get().AddEventListener(testEvent, listener_1);
    engine::EventDispatcher::Get().AddEventListener(testEvent, listener_2);
    engine::EventDispatcher::Get().Dispatch(testEvent, std::make_unique<engine::Event>());

    EXPECT_EQ(calls, 2);
}

#pragma endregion

#pragma region Edge Cases

TEST_F(EventDispatcherTest, DispatchWithExpiredListener) {
    testing::internal::CaptureStdout();

    auto listener = std::make_shared<engine::EventListener>([](const engine::Event*) {});
    engine::EventDispatcher::Get().AddEventListener(testEvent, listener);
    listener.reset();

    engine::EventDispatcher::Get().Dispatch(testEvent, std::make_unique<engine::Event>());
    auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, ::testing::HasSubstr("Removed expired"));
}

TEST_F(EventDispatcherTest, RemoveNonExistentListener) {
    testing::internal::CaptureStdout();

    auto listener = std::make_shared<engine::EventListener>([](const engine::Event*) {});
    engine::EventDispatcher::Get().RemoveEventListener("NonExistentEvent", listener);
    auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, ::testing::HasSubstr("Attempting to remove"));
}

#pragma endregion