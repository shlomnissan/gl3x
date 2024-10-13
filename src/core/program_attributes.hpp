// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "materials/material.hpp"

#include <string>

namespace engine {

struct ProgramAttributes {
    Material* material;

    bool color {false};
    bool texture_map {false};

    explicit ProgramAttributes(Material* material);

    auto PremutationKey() const -> std::string;
};

}