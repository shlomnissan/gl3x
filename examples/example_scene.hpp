/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gleam/nodes.hpp>
#include <gleam/cameras.hpp>

class ExampleScene : public gleam::Scene {
public:
    bool show_context_menu_ {true};

    virtual auto ContextMenu() -> void {
        // Empty
    }
};