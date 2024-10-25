// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "game.hpp"

Game::Game() {
    Add(dinosaur_);
    dinosaur_->TranslateX(20.0f);
    dinosaur_->TranslateY(20.0f);

    Add(ground_);
    ground_->TranslateX(300.0f);
    ground_->TranslateY(140.0f);
}