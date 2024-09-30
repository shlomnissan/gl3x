// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include "core/image.hpp"
#include "textures/texture.hpp"

#include <memory>
#include <string_view>

namespace engine {

/**
 * @brief Represents a 2D texture.
 */
class ENGINE_EXPORT Texture2D : public Texture {
public:
    /**
     * @brief Constructs a Texture2D object.
     *
     * @param image_path The path to the image file used to create the texture.
     */
    explicit Texture2D(std::string_view image_path);

    /**
     * @brief Checks if the texture has been loaded successfully.
     *
     * @return True if the texture is loaded, false otherwise.
     */
    [[nodiscard]]
    auto Loaded() const { return loaded_; }

    /**
     * @brief Retrieves the image associated with the texture.
     *
     * @return A const reference to the Image object.
     */
    [[nodiscard]]
    auto& Image() { return image_; }

    /**
     * @brief Creates a shared pointer to a Texture2D object.
     *
     * @param image_path The path to the image file used to create the texture.
     * @return A shared pointer to the created Texture2D object.
     */
    [[nodiscard]]
    static auto Create(std::string_view image_path) {
        return std::make_shared<Texture2D>(image_path);
    }

private:
    /// @brief The image associated with the texture.
    engine::Image image_;
    /// @brief Flag indicating whether the texture has been loaded.
    bool loaded_ {false};
};

}