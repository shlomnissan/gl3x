/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gleam/nodes.hpp>

class ExampleScene : public gleam::Scene {
public:
    bool show_context_menu_ {true};

    virtual auto ContextMenu() -> void = 0;
};