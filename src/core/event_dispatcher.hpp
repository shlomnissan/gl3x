// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "core/event.hpp"

#include <functional>
#include <memory>
#include <string_view>
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

    auto AddEventListener(const std::string& name, std::weak_ptr<EventListener> listener) {
        if (callbacks_.contains(name)) {
            callbacks_.at(name).emplace_back(listener);
        } else {
            callbacks_.emplace(name, std::vector{listener});
        }
    }

    auto Dispatch(const std::string& name, std::unique_ptr<Event> event) {
        if (!callbacks_.contains(name)) return;
        auto& callbacks = callbacks_[name];
        for (auto i = 0; i < callbacks.size(); ++i) {
            if (auto callback = callbacks[i].lock()) {
                (*callback)(event.get());
            }
        }
    }

private:
    EventDispatcher() = default;
    ~EventDispatcher() = default;

    std::unordered_map<std::string, std::vector<std::weak_ptr<EventListener>>> callbacks_;
};

}