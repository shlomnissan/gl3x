// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <type_traits>

namespace engine {

struct Event {
    bool handled {false};

    template<class T> requires std::is_base_of_v<Event, T>
    [[nodiscard]] auto Is() const {
        return dynamic_cast<const T*>(this) != nullptr;
    }

    template<class T> requires std::is_base_of_v<Event, T>
    [[nodiscard]] auto As() {
        return dynamic_cast<T*>(this);
    }

    template<class T> requires std::is_base_of_v<Event, T>
    [[nodiscard]] auto As() const {
        return dynamic_cast<const T*>(this);
    }

    virtual ~Event() = default;
};

struct KeyboardEvent : public Event {
    enum class Type {
        KeyPressed,
        KeyReleased
    };

    KeyboardEvent::Type type;

    explicit KeyboardEvent(KeyboardEvent::Type type) : type(type) {}
};

}