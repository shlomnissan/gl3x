// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/loaders/image_loader.hpp"

#include "loaders/image_loader_xyz.hpp"
#include "utilities/logger.hpp"

namespace engine {

ImageLoader::ImageLoader(const fs::path& path) : Loader(path) {}

auto ImageLoader::Load(const ImageCallback& callback) const -> void {
    if (!FileExists(path_)) {
        Logger::Log(LogLevel::Error, "Image file was not found '{}'", path_.string());
        return;
    }
    Loader::Load<Image>(callback);
}

auto ImageLoader::LoadImpl() const -> std::shared_ptr<void> {
    auto image = ImageLoaderXYZ::Load(path_);
    if (image) return std::make_shared<Image>(std::move(*image));
    return nullptr;
}

}