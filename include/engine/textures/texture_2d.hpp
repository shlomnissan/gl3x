// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

#include "engine/core/image.hpp"
#include "engine/math/transform2.hpp"
#include "engine/textures/texture.hpp"

#include <memory>
#include <string_view>

namespace engine {

/**
 * @brief Represents a 2D texture.
 */
class ENGINE_EXPORT Texture2D : public Texture {
public:
    /// @brief The UV transformation matrix.
    Transform2 transform;

    /**
     * @brief Constructs a Texture2D object.
     *
     * @param image A shared pointer to the image object used to create the texture.
     */
    explicit Texture2D(engine::Image image) : image_(std::move(image)) {}

    /**
     * @brief Retrieves the image associated with the texture.
     *
     * @return A pointer to the image object.
     */
    [[nodiscard]] auto& Image() { return image_; }

    /**
     * @brief Creates a shared pointer to a Texture2D object.
     *
     * @param image A shared pointer to the image object used to create the texture.
     * @return A shared pointer to the created Texture2D object.
     */
    [[nodiscard]] static auto Create(engine::Image image) {
        return std::make_shared<Texture2D>(image);
    }

    /**
     * @brief Retrieves the type of the texture.
     *
     * @return TextureType::Texture2D.
     */
    [[nodiscard]] auto Type() const -> TextureType override {
        return TextureType::Texture2D;
    }

    /**
     * @brief Set the offset of the texture on the X-axis.
     */
    auto OffsetX(float value) { transform.Translate({value, 0.0f}); }

    /**
     * @brief Set the offset of the texture on the Y-axis.
     */
    auto OffsetY(float value) { transform.Translate({0.0f, value}); }

    /**
     * @brief Set the uniform scale of the texture.
     */
    auto Scale(float value) { transform.Scale({value, value}); }

    /**
     * @brief Set the rotation angle of the texture.
     */
    auto Rotate(float angle) { transform.Rotate(angle); }

private:
    /// @brief The image associated with the texture.
    engine::Image image_;
};

}