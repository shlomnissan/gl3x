// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <gleam/nodes.hpp>

class ExampleScene : public engine::Scene {
public:
    bool show_context_menu_ {true};

    virtual auto ContextMenu() -> void = 0;
};