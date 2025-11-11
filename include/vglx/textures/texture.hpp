/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "vglx_export.h"

#include "vglx/core/disposable.hpp"
#include "vglx/core/identity.hpp"

namespace vglx {

/**
 * @brief Abstract base class for texture types.
 *
 * This class is not intended to be used directly. Use one of the concrete
 * texture types such as @ref Texture2D, or derive your own texture class
 * that implements the required interface.
 *
 * @ingroup TexturesGroup
 */
class VGLX_EXPORT Texture : public Disposable, public Identity {
public:
    /**
     * @brief Enumerates all supported texture types.
     */
    enum class Type {
        Texture2D, ///< Two-dimensional texture.
    };

    /**
     * @brief Specifies the byte alignment of each row in source texture data.
     *
     * Determines how pixel rows are aligned in memory when uploading texture
     * data to the GPU. The alignment value must match the source image’s
     * row stride to ensure correct decoding and avoid visual artifacts.
     *
     * Textures generated through the asset builder pipeline are encoded as
     * RGBA8 with 4-byte row alignment by default.
     */
    enum class RowAlignment : std::uint8_t {
        OneByte = 1, ///< 1-byte alignment (tightly packed).
        TwoBytes = 2, ///< 2-byte alignment.
        FourBytes = 4, ///< 4-byte alignment (default).
        EightBytes = 8 ///< 8-byte alignment
    };

    /**
     * @brief Renderer-specific texture handle.
     *
     * Typically corresponds to the underlying graphics API object identifier,
     * for example, an OpenGL texture ID.
     */
    unsigned int renderer_id = 0;

    /// @brief Current row alignment used when uploading texture data.
    RowAlignment row_alignment = RowAlignment::FourBytes;

    /**
     * @brief Identifies the concrete @ref Texture::Type "texture type".
     */
    [[nodiscard]] virtual auto GetType() const -> Type = 0;

    /**
     * @brief Destroys the texture and releases associated resources.
     */
    virtual ~Texture() {
        Dispose();
    }
};

}