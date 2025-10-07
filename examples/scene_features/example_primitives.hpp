/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <vglx/geometries.hpp>
#include <vglx/nodes.hpp>

#include <memory>
#include <string>

#include "example_scene.hpp"

class ExamplePrimitives : public ExampleScene {
public:
    ExamplePrimitives();

    auto OnAttached(SharedContextPointer context) -> void override;

    auto ContextMenu() -> void override;

private:
    vglx::BoxGeometry::Parameters box_params_;
    vglx::ConeGeometry::Parameters cone_params_;
    vglx::CylinderGeometry::Parameters cylinder_params_;
    vglx::PlaneGeometry::Parameters plane_params_;
    vglx::SphereGeometry::Parameters sphere_params_;

    std::string curr_primitive_  {"box"};
    std::shared_ptr<vglx::Mesh> mesh_;
    std::shared_ptr<vglx::Mesh> wireframes_;

    auto InitializeParams() -> void;
    auto BoxContextMenu(bool& dirty) -> void;
    auto ConeContextMenu(bool& dirty) -> void;
    auto CylinderContextMenu(bool& dirty) -> void;
    auto PlaneContextMenu(bool& dirty) -> void;
    auto SphereContextMenu(bool& dirty) -> void;
};