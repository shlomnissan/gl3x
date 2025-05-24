// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"
#include "engine/core/disposable.hpp"
#include "engine/core/identity.hpp"

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
    /**
     * @brief Retrieves the type of the texture.
     *
     * @return TextureType The type of the texture.
     */
    [[nodiscard]] virtual auto Type() const -> TextureType = 0;

    /**
     * @brief Destructor calls the Dispose() method to clean up resources.
     */
    ~Texture() {
        Dispose();
    }
};

}