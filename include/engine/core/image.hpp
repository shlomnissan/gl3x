// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include <vector>

namespace engine {

using ImageData = std::vector<unsigned char>;

class ENGINE_EXPORT Image {
public:
    /**
     * @brief Structure to hold the metadata for an image.
     */
    struct Parameters {
        unsigned int width;     ///< Width of the image in pixels.
        unsigned int height;    ///< Height of the image in pixels.
        unsigned int depth;     ///< Depth of the image (e.g., number of color channels).
        unsigned int flipped = true; ///< Indicates if the image data is flipped.
    };

    /**
     * @brief Constructs an Image object.
     *
     * @param data Rvalue reference to the image data.
     * @param params Parameters for the image.
     */
    Image(ImageData&& data, const Parameters& params) :
        width_(params.width),
        height_(params.height),
        depth_(params.depth),
        flipped_(params.flipped),
        data_(std::move(data)) {}

    /**
     * @brief Gets the image data.
     *
     * @return A constant reference to the image data.
     */
    [[nodiscard]]
    auto Data() const -> const ImageData& {
        return data_;
    }

private:
    /// @brief Image data (pixel values).
    ImageData data_;
    /// @brief Width of the image in pixels.
    unsigned int width_;
    /// @brief Height of the image in pixels.
    unsigned int height_;
    /// @brief Depth of the image (e.g., number of color channels).
    unsigned int depth_;
    /// @brief Indicates if the image data is flipped.
    bool flipped_;
};

}