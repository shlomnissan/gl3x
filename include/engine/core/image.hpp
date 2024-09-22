// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include <memory>

namespace engine {

using ImageDataPtr = std::unique_ptr<unsigned char[], void(*)(void*)>;

/**
 * @brief Represents an image with associated metadata and pixel data.
 */
class ENGINE_EXPORT Image {
public:
    /**
     * @brief Structure to hold the metadata for an image.
     */
    struct ImageMetadata {
        unsigned int width;     ///< Width of the image in pixels.
        unsigned int height;    ///< Height of the image in pixels.
        unsigned int depth;     ///< Depth of the image (e.g., number of color channels).
    };

    /**
     * @brief Constructs an Image object.
     *
     * @param params Parameters for the image metadata.
     * @param data Pointer to the image data managed by a unique_ptr.
     */
    Image(const ImageMetadata& params, ImageDataPtr data) :
        data_(std::move(data)),
        width_(params.width),
        height_(params.height),
        depth_(params.depth) {}

    /**
     * @brief Gets the image data.
     *
     * @return A pointer to the image data.
     */
    [[nodiscard]] auto Data() const { return data_.get(); }

    /**
     * @brief Gets the width of the image.
     *
     * @return The width in pixels.
     */
    [[nodiscard]] auto Width() const { return width_; }

    /**
     * @brief Gets the height of the image.
     *
     * @return The height in pixels.
     */
    [[nodiscard]] auto Height() const { return height_; }

    /**
     * @brief Gets the depth of the image.
     *
     * @return The number of color channels.
     */
    [[nodiscard]] auto Depth() const { return depth_; }

private:
    ImageDataPtr data_;     ///< Pointer to the image data.
    unsigned int width_;    ///< Width of the image in pixels.
    unsigned int height_;   ///< Height of the image in pixels.
    unsigned int depth_;    ///< Depth of the image (e.g., number of color channels).
};

}