/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <vglx/nodes.hpp>
#include <vglx/cameras.hpp>

class ExampleScene : public vglx::Scene {
public:
    bool show_context_menu_ {true};

    virtual auto ContextMenu() -> void {
        // Empty
    }
};