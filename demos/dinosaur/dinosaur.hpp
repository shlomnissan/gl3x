// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <memory>

#include <engine/scene/game_node.hpp>
#include <engine/materials/flat_material.hpp>
#include <engine/scene/mesh.hpp>

class Dinosaur : public engine::GameNode {
public:
    Dinosaur();

    auto Update(double delta) -> void override;

    auto OnKeyboardEvent(engine::KeyboardEvent* event) -> void override;

private:
    std::shared_ptr<engine::Mesh> mesh_;
    std::shared_ptr<engine::FlatMaterial> material_;
};