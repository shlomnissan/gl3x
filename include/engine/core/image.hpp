// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine/core/disposable.hpp"

#include <functional>
#include <string>
#include <memory>

namespace engine {

using ImageData = std::unique_ptr<unsigned char[], std::function<void(void*)>>;

/**
* @brief Metadata for an image.
*/
struct ImageMetadata {
    std::string filename; ///< The filename of the image.
    unsigned int width; ///< The width of the image.
    unsigned int height; ///< The height of the image.
    unsigned int depth; ///< The depth of the image (number of channels).
};

/**
 * @brief A class representing an image, which can be loaded and disposed of.
 */
class Image : public Disposable {
public:
    /// @brief The filename of the image.
    std::string filename {};

    /// @brief The width of the image.
    unsigned int width {0};

    /// @brief The height of the image.
    unsigned int height {0};

    /// @brief The depth of the image.
    unsigned int depth {0};

    /**
     * @brief Constructs an Image object with the given metadata and image data.
     *
     * @param params The metadata for the image.
     * @param data The image data.
     */
    Image(const ImageMetadata& params, ImageData data);

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

    /**
     * @brief Gets the image data.
     *
     * @return unsigned char* A pointer to the image data.
     */
    [[nodiscard]] auto Data() const { return data_.get(); }

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
    ImageData data_ {nullptr, [](void*){}};

    /**
     * @brief Resets the state of the other Image object.
     *
     * @param other The other Image object to reset.
     */
    auto Reset(Image& instance) const -> void;
};

}