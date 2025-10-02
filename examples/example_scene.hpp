/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gl3x/nodes.hpp>
#include <gl3x/cameras.hpp>

class ExampleScene : public gl3x::Scene {
public:
    bool show_context_menu_ {true};

    virtual auto ContextMenu() -> void {
        // Empty
    }
};