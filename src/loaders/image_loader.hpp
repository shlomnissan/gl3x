// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

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