// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

namespace engine {

class ENGINE_EXPORT Vector3 {
public:
    float x;
    float y;
    float z;

    Vector3();

    explicit Vector3(float value);
    
    Vector3(float x, float y, float z);
};

};