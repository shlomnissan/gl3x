// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <gleam/geometries.hpp>
#include <gleam/nodes.hpp>

#include <memory>
#include <string>

#include "example_scene.hpp"

class ExamplePrimitiveMesh : public ExampleScene {
public:
    explicit ExamplePrimitiveMesh(std::shared_ptr<engine::Camera>);

    auto ContextMenu() -> void override;

private:
    engine::BoxGeometry::Parameters box_params_;
    engine::ConeGeometry::Parameters cone_params_;
    engine::CylinderGeometry::Parameters cylinder_params_;
    engine::PlaneGeometry::Parameters plane_params_;
    engine::SphereGeometry::Parameters sphere_params_;

    std::string curr_primitive_ = "box";
    std::shared_ptr<engine::Mesh> mesh_;
    std::shared_ptr<engine::Mesh> wireframes_;

    auto InitializeParams() -> void;
    auto BoxContextMenu(bool& dirty) -> void;
    auto ConeContextMenu(bool& dirty) -> void;
    auto CylinderContextMenu(bool& dirty) -> void;
    auto PlaneContextMenu(bool& dirty) -> void;
    auto SphereContextMenu(bool& dirty) -> void;
};