// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/event_dispatcher.hpp"

namespace engine {

auto EventDispatcher::AddEventListener(const std::string& name, std::weak_ptr<EventListener> listener) -> void {
    if (callbacks_.contains(name)) {
        callbacks_.at(name).emplace_back(listener);
    } else {
        callbacks_.try_emplace(name, std::vector{listener});
    }
}

auto EventDispatcher::RemoveEventListener(const std::string& name, std::shared_ptr<EventListener> listener) -> void {
    auto removed_callbacks = 0UL;
    if (callbacks_.contains(name)) {
        auto& callbacks = callbacks_[name];
        removed_callbacks = std::erase_if(callbacks, [&listener](const auto& callback) {
            if (auto c = callback.lock()) return c == listener;
            return false;
        });
    }

    if (removed_callbacks == 0) {
        Logger::Log(
            LogLevel::Warning,
            "Attempting to remove an event listener that doesn't exist '{}'",
            name
        );
    }
}

auto EventDispatcher::Dispatch(const std::string& name, std::unique_ptr<Event> event) -> void {
    if (!callbacks_.contains(name)) {
        Logger::Log(
            LogLevel::Warning,
            "Attempting to dispatch an event that doesn't exist '{}'",
            name
        );
        return;
    }

    auto& callbacks = callbacks_[name];
    for (auto iter = begin(callbacks); iter != end(callbacks);) {
        if (const auto& callback = iter->lock()) {
            (*callback)(event.get());
            iter++;
        } else {
            Logger::Log(LogLevel::Warning, "Removed expired event listener '{}'", name);
            callbacks.erase(iter);
        }
    }
}

}