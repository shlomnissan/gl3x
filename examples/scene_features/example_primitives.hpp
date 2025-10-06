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
    gl3x::BoxGeometry::Parameters box_params_;
    gl3x::ConeGeometry::Parameters cone_params_;
    gl3x::CylinderGeometry::Parameters cylinder_params_;
    gl3x::PlaneGeometry::Parameters plane_params_;
    gl3x::SphereGeometry::Parameters sphere_params_;

    std::string curr_primitive_  {"box"};
    std::shared_ptr<gl3x::Mesh> mesh_;
    std::shared_ptr<gl3x::Mesh> wireframes_;

    auto InitializeParams() -> void;
    auto BoxContextMenu(bool& dirty) -> void;
    auto ConeContextMenu(bool& dirty) -> void;
    auto CylinderContextMenu(bool& dirty) -> void;
    auto PlaneContextMenu(bool& dirty) -> void;
    auto SphereContextMenu(bool& dirty) -> void;
};