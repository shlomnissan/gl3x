// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/core/image.hpp"

#include <filesystem>
#include <optional>

namespace engine {

namespace fs = std::filesystem;

/**
 * @brief A class responsible for loading images from disk.
 */
class ENGINE_EXPORT ImageLoader {
public:
    /**
     * @brief Loads an image from the specified file path.
     *
     * This function attempts to read the image from the file and returns an
     * optional `Image` object. If the image loading fails (e.g., file not found,
     * invalid format), it returns `std::nullopt`.
     *
     * @param path The file system path to the image file.
     * @param flip_y Whether to flip the image vertically (along the Y-axis). Defaults to true.
     * @return An `std::optional<Image>` containing the image data and metadata, or
     *         `std::nullopt` if loading fails.
     */
    [[nodiscard]]
    static auto Load(const fs::path& path, bool flip_y = true) -> std::optional<Image>;
};

}