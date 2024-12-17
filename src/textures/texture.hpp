// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/math/transform_2d.hpp"

#include "core/disposable.hpp"
#include "core/identity.hpp"

namespace engine {

class Texture : public Disposable, public Identity {
public:
    Transform2D transform;
};

}