// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"
#include "engine/core/disposable.hpp"
#include "engine/core/identity.hpp"

namespace engine {

/**
 * @brief Represents available texture types.
 * @ingroup TexturesGroup
 */
enum class TextureType {
    Texture2D
};

/**
 * @brief Base class for texture objects. It provides a common interface for
 * all texture types, which currently includes Texture2D. Not intended to be
 * instantiated directly.
 *
 * @ingroup TexturesGroup
 */
class ENGINE_EXPORT Texture : public Disposable, public Identity {
public:
    /**
     * @brief Returns texture type.
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