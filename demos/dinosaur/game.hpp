// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <memory>

#include <engine/scene/scene.hpp>

#include "dinosaur.hpp"
#include "ground.hpp"

class Game : public engine::Scene {
public:
    Game();

private:
    std::shared_ptr<Dinosaur> dinosaur_ = std::make_shared<Dinosaur>();
    std::shared_ptr<Ground> ground_ = std::make_shared<Ground>();
};