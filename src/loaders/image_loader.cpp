// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/loaders/image_loader.hpp"

#include "loaders/image_loader_xyz.hpp"
#include "utilities/logger.hpp"

namespace engine {

auto ImageLoader::Load(const fs::path& path, const ImageCallback& callback) const -> void {
    if (!FileExists(path)) {
        Logger::Log(LogLevel::Error, "Image file was not found '{}'", path.string());
        return;
    }
    Loader::Load<Image>(path, callback);
}

auto ImageLoader::LoadImpl(const fs::path& path) const -> std::shared_ptr<void> {
    if (auto image = ImageLoaderXYZ::Load(path)) {
        return std::make_shared<Image>(std::move(*image));
    }
    return nullptr;
}

}