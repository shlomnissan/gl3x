// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "core/event.hpp"
#include "core/logger.hpp"

#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace engine {

using EventListener = std::function<void(Event*)>;

class EventDispatcher {
public:
    EventDispatcher(const EventDispatcher&) = delete;
    EventDispatcher& operator=(const EventDispatcher&) = delete;

    static auto Get() -> EventDispatcher& {
        static auto instance = EventDispatcher {};
        return instance;
    }

    auto AddEventListener(const std::string& name, std::weak_ptr<EventListener> listener) -> void;

    auto RemoveEventListener(const std::string& name, std::shared_ptr<EventListener> listener) -> void;

    auto Dispatch(const std::string& name, std::unique_ptr<Event> event) -> void;

private:
    EventDispatcher() = default;
    ~EventDispatcher() = default;

    std::unordered_map<std::string, std::vector<std::weak_ptr<EventListener>>> callbacks_;
};

}