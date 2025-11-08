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
     * @brief Renderer-specific texture handle.
     *
     * Typically corresponds to the underlying graphics API object identifier,
     * for example, an OpenGL texture ID.
     */
    unsigned int renderer_id = 0;

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