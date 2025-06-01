// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "gleam_export.h"

#include "gleam/loaders.hpp"

#include <memory>

namespace engine {

class GLEAM_EXPORT SharedContext {
public:
    /**
     * @brief Holds shared parameters for the context.
     */
    struct SharedParameters {
        float ratio; ///< Aspect ratio of the buffer.
        int width;   ///< Width of the buffer in pixels.
        int height;  ///< Height of the buffer in pixels.
        bool debug;  ///< Debug mode flag.
    };

    /**
     * @brief Holds shared loaders for various resources.
     */
    struct SharedLoaders {
        /// @brief Loader for image resources.
        std::shared_ptr<TextureLoader> Texture = TextureLoader::Create();

        /// @brief Loader for mesh resources.
        std::shared_ptr<MeshLoader> Mesh = MeshLoader::Create();
    };

    /**
     * @brief Default constructor.
     */
    explicit SharedContext(const SharedParameters& params) : params_(params) {};

    /**
     * @brief Retrieves the shared parameters of the context.
     *
     * @return A constant reference to the shared parameters.
     */
    [[nodiscard]] const SharedParameters& Parameters() const {
        return params_;
    }

    /**
     * @brief Retrieves the shared loaders for various resources.
     *
     * @return A constant reference to the shared loaders.
     */
    [[nodiscard]] const SharedLoaders& Loaders() const {
        return loaders_;
    }

private:
    /// @brief Shared parameters.
    SharedParameters params_ {};

    /// @brief Shared loaders.
    SharedLoaders loaders_ {};
};

}