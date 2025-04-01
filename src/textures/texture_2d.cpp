// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/textures/texture_2d.hpp"

#include "loaders/image_loader_xyz.hpp"
#include "utilities/logger.hpp"

namespace engine {

Texture2D::Texture2D(std::string_view image_path) {
    auto image = ImageLoaderXYZ::Load(image_path);
    if (image.has_value()) {
        image_ = std::move(image.value());
        loaded_ = true;
    } else {
        Logger::Log(LogLevel::Error, "Failed to initialize 2D texture UUID({})", UUID());
    }
}

}