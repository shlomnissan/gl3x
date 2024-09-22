// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include "core/image.hpp"

#include <filesystem>
#include <optional>

namespace engine {

namespace fs = std::filesystem;

class ENGINE_EXPORT ImageLoader {
public:
    [[nodiscard]]
    static auto Load(const fs::path& path, bool flip_y = true) -> std::optional<Image>;
};

}