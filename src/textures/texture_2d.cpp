// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/textures/texture_2d.hpp"

#include "engine/loaders/image_loader.hpp"

#include "utilities/logger.hpp"

namespace engine {

Texture2D::Texture2D(std::string_view image_path) {
    auto image_loader = ImageLoader {};
    image_loader.Load(image_path, [this](std::shared_ptr<engine::Image> image) {
        if (image == nullptr) {
            Logger::Log(LogLevel::Error, "Failed to initialize 2D texture UUID({})", UUID());
            return;
        }
        image_ = image;
        loaded_ = true;
    });
}

}