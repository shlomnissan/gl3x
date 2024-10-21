// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/scene/node.hpp"

#include <memory>
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

struct SceneEvent : public Event {
    enum class Type {
        AddedToScene,
        RemovedFromScene
    };

    std::shared_ptr<Node> node;
    SceneEvent::Type type;

    SceneEvent(Type type, std::shared_ptr<Node> node) : type(type), node(node) {}
};

struct KeyboardEvent : public Event {
    enum class Type {
        KeyPressed,
        KeyReleased
    };

    KeyboardEvent::Type type;

    explicit KeyboardEvent(Type type) : type(type) {}
};

}