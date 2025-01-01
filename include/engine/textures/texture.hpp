// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"
#include "engine/math/transform_2d.hpp"

#include "core/disposable.hpp"
#include "core/identity.hpp"

namespace engine {

/**
 * @brief The type of texture.
 */
enum class TextureType {
    Texture2D
};

/**
 * @brief Abstract base class for textures.
 */
class ENGINE_EXPORT Texture : public Disposable, public Identity {
public:
    /// @brief The UV transformation matrix.
    Transform2D transform;

    /**
     * @brief Retrieves the type of the texture.
     *
     * @return TextureType The type of the texture.
     */
    [[nodiscard]] virtual auto Type() const -> TextureType = 0;

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