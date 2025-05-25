// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/loaders/texture_loader.hpp"

#include "asset_builder/include/types.hpp"

#include <cstring>
#include <fstream>

namespace engine {

auto TextureLoader::LoadImpl(const fs::path& path) const -> std::expected<std::shared_ptr<void>, std::string> {
    auto file = std::ifstream {path, std::ios::binary};
    if (!file) {
        return std::unexpected(std::format("Unable to open file '{}'", path.string()));
    }

    auto header = TextureHeader {};
    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    if (std::memcmp(header.magic, "TEX0", 4) != 0) {
        return std::unexpected(std::format("Invalid texture file '{}'", path.string()));
    }

    if (header.version != 1 || header.header_size != sizeof(TextureHeader)) {
        return std::unexpected(std::format("Unsupported texture version in file '{}'", path.string()));
    }

    auto data = std::vector<uint8_t>(header.pixel_data_size);
    file.read(reinterpret_cast<char*>(data.data()), header.pixel_data_size);

    auto texture = std::make_shared<Texture2D>(Texture2D::Parameters {
        .width = header.width,
        .height = header.height,
        .data = std::move(data)
    });

    texture->SetName(path.filename().string());

    return texture;
}

}