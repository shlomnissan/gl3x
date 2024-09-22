// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/loaders/image_loader.hpp"

#include "core/logger.hpp"

namespace engine {

auto ImageLoader::Load(const fs::path& path, bool flip_y = true) -> Image {
    // TODO: implement
    return Image {{
        .width = 0,
        .height = 0,
        .depth = 0,
    }, {}};
}

}