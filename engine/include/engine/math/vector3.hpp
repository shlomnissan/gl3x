// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine_export.h"

namespace engine {

struct ENGINE_EXPORT Vector3 {
    float x;
    float y;
    float z;

    Vector3();
    Vector3(float value);
    Vector3(float x, float y, float z);
};

};