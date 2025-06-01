// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "gleam_export.h"

#include "gleam/math/transform2.hpp"
#include "gleam/textures/texture.hpp"

#include <memory>
#include <string_view>

namespace gleam {

/**
 * @brief Represents a 2D texture that can be attached to materials. While you
 * can instantiate a Texture2D object directly, it is recommended to use the texture
 * loader object to create texture instances:
 *
 * @code
 * auto MyNode::OnAttached() -> void override {
 *   this->Context()->Loaders().Texture->LoadAsync(
 *     "assets/my_texture.tex",
 *     [this](auto result) { texture_ = result.value(); }
 *   );
 * }
 * @endcode
 *
 * @ingroup TexturesGroup
 */
class GLEAM_EXPORT Texture2D : public Texture {
public:
    /// @brief Width in pixels.
    unsigned width;

    /// @brief Height in pixels.
    unsigned height;

    /// @brief Underlying texture data.
    std::vector<uint8_t> data {};

    /// @brief Parameters for constructing a texture2D object.
    struct Parameters {
        unsigned width; ///< Width in pixels.
        unsigned height; ///< Height in pixels.
        std::vector<uint8_t> data; ///< Underlying texture data.
    };

    /**
     * @brief Constructs a Texture2D object.
     *
     * @param params Texture2D::Parameters
     */
    explicit Texture2D(const Parameters& params) :
        width(params.width),
        height(params.height),
        data(std::move(params.data)) {}

    /**
     * @brief Creates a shared pointer to a Texture2D object.
     *
     * @param params Texture2D::Parameters
     * @return std::shared_ptr<Texture2D>
     */
    [[nodiscard]] static auto Create(const Parameters& params) {
        return std::make_shared<Texture2D>(params);
    }

    /**
     * @brief Returns texture type.
     *
     * @return TextureType::Texture2D
     */
    [[nodiscard]] auto GetType() const -> TextureType override {
        return TextureType::Texture2D;
    }

    /**
     * @brief Returns the transformation matrix for UV mapping.
     *
     * @return Matrix3
     */
    [[nodiscard]] auto GetTransform() {
        return transform_.Get();
    }

    /**
     * @brief Sets texture offset on the X-axis.
     *
     * @param value Offset value in pixels.
     */
    auto OffsetX(float value) { transform_.Translate({value, 0.0f}); }

    /**
     * @brief Sets texture offset on the Y-axis.
     *
     * @param value Offset value in pixels.
     */
    auto OffsetY(float value) { transform_.Translate({0.0f, value}); }

    /**
     * @brief Sets uniform scale.
     *
     * @param value Scale value.
     */
    auto Scale(float value) { transform_.Scale({value, value}); }

    /**
     * @brief Sets rotation angle.
     *
     * @param angle Rotation angle in radians.
     */
    auto Rotate(float angle) { transform_.Rotate(angle); }

private:
    /// @brief UV transformation matrix.
    Transform2 transform_;
};

}