// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

#include "engine/core/image.hpp"
#include "engine/textures/texture.hpp"

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
     * @param image A shared pointer to the image object used to create the texture.
     */
    explicit Texture2D(std::shared_ptr<engine::Image> image) : image_(image) {}

    /**
     * @brief Retrieves the image associated with the texture.
     *
     * @return A pointer to the image object.
     */
    [[nodiscard]] auto Image() { return image_.get(); }

    /**
     * @brief Creates a shared pointer to a Texture2D object.
     *
     * @param image A shared pointer to the image object used to create the texture.
     * @return A shared pointer to the created Texture2D object.
     */
    [[nodiscard]] static auto Create(std::shared_ptr<engine::Image> image) {
        return std::make_shared<Texture2D>(image);
    }

    /**
     * @brief Retrieves the type of the texture.
     *
     * @return TextureType::Texture2D.
     */
    [[nodiscard]] auto Type() const -> TextureType override {
        return TextureType::Texture2D;
    }

private:
    /// @brief The image associated with the texture.
    std::shared_ptr<engine::Image> image_;
};

}