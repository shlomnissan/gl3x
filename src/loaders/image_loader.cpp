// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#define STB_IMAGE_IMPLEMENTATION

#include "engine/loaders/image_loader.hpp"

#include "utilities/logger.hpp"

#include <stb_image.h>

namespace engine {

auto ImageLoader::LoadImpl(const fs::path& path) const -> std::shared_ptr<void> {
    stbi_set_flip_vertically_on_load(flip_y);

    auto width = 0;
    auto height = 0;
    auto depth = 0;
    auto data = stbi_load(path.string().c_str(), &width, &height, &depth, 4);

    if (data == nullptr) {
        Logger::Log(LogLevel::Error, "Failed to load image '{}'", path.string());
        return nullptr;
    }

    return std::make_shared<Image>(Image {{
        .filename = path.filename().string(),
        .width = static_cast<unsigned int>(width),
        .height = static_cast<unsigned int>(height),
        .depth = static_cast<unsigned int>(depth)
    }, ImageDataPtr(data, &stbi_image_free)});
}

}