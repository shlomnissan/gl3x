// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/scene/node.hpp"

#include "core/event.hpp"

namespace engine {

class GameNode : public Node {
public:
    virtual auto Update(double delta) -> void = 0;

    virtual auto OnKeyboardEvent(KeyboardEvent* event) -> void = 0;
};

}