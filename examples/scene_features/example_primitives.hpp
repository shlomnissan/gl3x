/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gleam/geometries.hpp>
#include <gleam/nodes.hpp>

#include <memory>
#include <string>

#include "example_scene.hpp"

class ExamplePrimitives : public ExampleScene {
public:
    ExamplePrimitives();

    auto OnAttached(gleam::SharedContext* context) -> void override;

    auto ContextMenu() -> void override;

private:
    gleam::CubeGeometry::Parameters box_params_;
    gleam::ConeGeometry::Parameters cone_params_;
    gleam::CylinderGeometry::Parameters cylinder_params_;
    gleam::PlaneGeometry::Parameters plane_params_;
    gleam::SphereGeometry::Parameters sphere_params_;

    std::string curr_primitive_  {"box"};
    std::shared_ptr<gleam::Mesh> mesh_;
    std::shared_ptr<gleam::Mesh> wireframes_;

    auto InitializeParams() -> void;
    auto BoxContextMenu(bool& dirty) -> void;
    auto ConeContextMenu(bool& dirty) -> void;
    auto CylinderContextMenu(bool& dirty) -> void;
    auto PlaneContextMenu(bool& dirty) -> void;
    auto SphereContextMenu(bool& dirty) -> void;
};