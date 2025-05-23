// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

#include <string>
#include <vector>

namespace engine {

struct ENGINE_EXPORT Image {
    std::string filename;
    std::vector<uint8_t> data;
    unsigned int width;
    unsigned int height;
    unsigned int channels;
};

}