// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

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
    /// @brief Width of the texture in pixels.
    unsigned width;

    /// @brief Height of the texture in pixels.
    unsigned height;

    /// @brief Underlying texture data.
    std::vector<uint8_t> data {};

    /// @brief The UV transformation matrix.
    Transform2 transform;

    /// @brief Parameters for configuring the texture.
    struct Parameters {
        unsigned width; ///< Width of the texture in pixels.
        unsigned height; ///< Height of the texture in pixels.
        std::vector<uint8_t> data; ///< Underlying texture data.
    };

    /**
     * @brief Constructs a Texture2D object.
     *
     * @param params Parameters struct of the texture.
     */
    explicit Texture2D(const Parameters& params) :
        width(params.width),
        height(params.height),
        data(std::move(params.data)) {}

    /**
     * @brief Creates a shared pointer to a Texture2D object.
     *
     * @param params Parameters struct of the texture.
     * @return A shared pointer to the created Texture2D object.
     */
    [[nodiscard]] static auto Create(const Parameters& params) {
        return std::make_shared<Texture2D>(params);
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
};

}