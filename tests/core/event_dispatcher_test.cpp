/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "events/event_dispatcher.hpp"

#include <memory>
#include <string>

class EventDispatcherTest : public ::testing::Test {
protected:
    void TearDown() override {
        vglx::EventDispatcher::Get().RemoveEventListenersForEvent(testEvent);
    }

    std::string testEvent {"TestEvent"};
};

#pragma region Event Listener Management

TEST_F(EventDispatcherTest, AddEventListener) {
    auto calls = 0;
    auto listener = std::make_shared<vglx::EventListener>(
        [&calls](const vglx::Event*) { calls++; }
    );

    vglx::EventDispatcher::Get().AddEventListener(testEvent, listener);
    vglx::EventDispatcher::Get().Dispatch(testEvent, std::make_unique<vglx::Event>());

    EXPECT_EQ(calls, 1);
}

TEST_F(EventDispatcherTest, RemoveEventListener) {
    auto calls = 0;
    auto listener = std::make_shared<vglx::EventListener>(
        [&calls](const vglx::Event*) { calls++; }
    );

    vglx::EventDispatcher::Get().AddEventListener(testEvent, listener);
    vglx::EventDispatcher::Get().RemoveEventListener(testEvent, listener);
    vglx::EventDispatcher::Get().Dispatch(testEvent, std::make_unique<vglx::Event>());

    EXPECT_EQ(calls, 0);
}

#pragma endregion

#pragma region Event Dispatching

TEST_F(EventDispatcherTest, DispatchToSingleListener) {
    auto calls = 0;
    auto listener = std::make_shared<vglx::EventListener>(
        [&calls](const vglx::Event*) { calls++; }
    );

    vglx::EventDispatcher::Get().AddEventListener(testEvent, listener);
    vglx::EventDispatcher::Get().Dispatch(testEvent, std::make_unique<vglx::Event>());

    EXPECT_EQ(calls, 1);
}

TEST_F(EventDispatcherTest, DispatchToMultipleListeners) {
    auto calls = 0;

    auto listener_1 = std::make_shared<vglx::EventListener>(
        [&calls](const vglx::Event*) { calls++; }
    );

    auto listener_2 = std::make_shared<vglx::EventListener>(
        [&calls](const vglx::Event*) { calls++; }
    );

    vglx::EventDispatcher::Get().AddEventListener(testEvent, listener_1);
    vglx::EventDispatcher::Get().AddEventListener(testEvent, listener_2);
    vglx::EventDispatcher::Get().Dispatch(testEvent, std::make_unique<vglx::Event>());

    EXPECT_EQ(calls, 2);
}

#pragma endregion

#pragma region Edge Cases

TEST_F(EventDispatcherTest, DispatchWithExpiredListener) {
    testing::internal::CaptureStdout();

    auto listener = std::make_shared<vglx::EventListener>([](const vglx::Event*) {});
    vglx::EventDispatcher::Get().AddEventListener(testEvent, listener);
    listener.reset();

    vglx::EventDispatcher::Get().Dispatch(testEvent, std::make_unique<vglx::Event>());
    auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, ::testing::HasSubstr("Removed expired"));
}

TEST_F(EventDispatcherTest, RemoveNonExistentListener) {
    testing::internal::CaptureStdout();

    auto listener = std::make_shared<vglx::EventListener>([](const vglx::Event*) {});
    vglx::EventDispatcher::Get().RemoveEventListener("NonExistentEvent", listener);
    auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, ::testing::HasSubstr("Attempting to remove"));
}

#pragma endregion