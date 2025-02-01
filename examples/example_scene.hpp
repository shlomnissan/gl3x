// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/nodes.hpp>

class ExampleScene : public engine::Scene {
public:
    virtual auto ContextMenu() -> void = 0;
};