/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/core/disposable.hpp"
#include "gleam/core/identity.hpp"

namespace gleam {

/**
 * @brief Represents available texture types.
 * @ingroup TexturesGroup
 */
enum class TextureType {
    Texture2D
};

/**
 * @brief **Abstract** base class for texture objects.
 *
 * This class provides a common interface for all texture types, which
 * currently includes Texture2D. Not intended to be instantiated directly.
 *
 * @ingroup TexturesGroup
 */
class GLEAM_EXPORT Texture : public Disposable, public Identity {
public:
    /// @brief Renderer-specific identifier assigned by the graphics API
    unsigned int renderer_id = 0;

    /**
     * @brief Returns texture type.
     *
     * @return TextureType
     */
    [[nodiscard]] virtual auto GetType() const -> TextureType = 0;

    /**
     * @brief Calls Dispose() to clean up resources.
     */
    ~Texture() {
        Dispose();
    }
};

}