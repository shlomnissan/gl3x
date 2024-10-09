// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "materials/material.hpp"

namespace engine {

struct ProgramAttributes {
    Material* material;

    bool color {false};

    explicit ProgramAttributes(Material* material);
};

}