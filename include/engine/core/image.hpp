// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine/core/disposable.hpp"

#include <string>
#include <memory>

namespace engine {

using ImageDataPtr = std::unique_ptr<unsigned char[], void(*)(void*)>;

/**
* @brief Metadata for an image.
*/
struct ImageMetadata {
    std::string filename;
    unsigned int width;
    unsigned int height;
    unsigned int depth;
};

/**
 * @brief A class representing an image, which can be loaded and disposed of.
 */
class Image : public Disposable {
public:
    /**
     * @brief Default constructor.
     */
    Image() = default;

    /**
     * @brief Constructs an Image object with the given metadata and image data.
     *
     * @param params The metadata for the image.
     * @param data The image data.
     */
    Image(const ImageMetadata& params, ImageDataPtr data);

    /**
     * @brief Move constructor.
     *
     * @param other The other Image object to move from.
     */
    Image(Image&& other) noexcept;

    /**
     * @brief Move assignment operator.
     *
     * @param other The other Image object to move from.
     * @return Image& A reference to the updated Image object.
     */
    auto operator=(Image&& other) noexcept -> Image&;

    [[nodiscard]] auto Filename() const { return filename_; }

    /**
     * @brief Gets the image data.
     *
     * @return unsigned char* A pointer to the image data.
     */
    [[nodiscard]] auto Data() const { return data_.get(); }

    /**
     * @brief Gets the width of the image.
     *
     * @return unsigned int The width of the image in pixels.
     */
    [[nodiscard]] auto Width() const { return width_; }

    /**
     * @brief Gets the height of the image.
     *
     * @return unsigned int The height of the image in pixels.
     */
    [[nodiscard]] auto Height() const { return height_; }

    /**
     * @brief Gets the depth of the image.
     *
     * @return unsigned int The depth of the image (e.g., number of color channels).
     */
    [[nodiscard]] auto Depth() const { return depth_; }

    /**
     * @brief Disposes of the image data.
     */
    auto Dispose() -> void override;

    /**
     * @brief Destructor for the Image class.
     */
    ~Image() override {
        Image::Dispose();
    }

private:
    /// @brief The image data.
    ImageDataPtr data_ {nullptr, [](void*){}};

    /// @brief The filename of the image.
    std::string filename_ {};

    /// @brief The width of the image.
    unsigned int width_ {0};

    /// @brief The height of the image.
    unsigned int height_ {0};

    /// @brief The depth of the image.
    unsigned int depth_ {0};

    /**
     * @brief Resets the state of the other Image object.
     *
     * @param other The other Image object to reset.
     */
    auto Reset(Image& instance) const -> void;
};

}