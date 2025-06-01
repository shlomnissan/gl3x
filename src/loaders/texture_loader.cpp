// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "gleam/loaders/texture_loader.hpp"

#include "utilities/file.hpp"

#include "asset_builder/include/types.hpp"

#include <cstring>
#include <fstream>

namespace gleam {

auto TextureLoader::LoadImpl(const fs::path& path) const -> LoaderResult<Texture2D> {
    auto file = std::ifstream {path, std::ios::binary};
    auto path_s = path.string();
    if (!file) {
        return std::unexpected(
            std::format("Unable to open file '{}'", path_s)
        );
    }

    auto header = TextureHeader {};
    read_binary(file, header);
    if (std::memcmp(header.magic, "TEX0", 4) != 0) {
        return std::unexpected(
            std::format("Invalid texture file '{}'", path_s)
        );
    }

    if (header.version != 1 || header.header_size != sizeof(TextureHeader)) {
        return std::unexpected(
            std::format("Unsupported texture version in file '{}'", path_s)
        );
    }

    auto data = std::vector<uint8_t>(header.pixel_data_size);
    read_binary(file, data, header.pixel_data_size);

    auto texture = std::make_shared<Texture2D>(Texture2D::Parameters {
        .width = header.width,
        .height = header.height,
        .data = std::move(data)
    });

    texture->SetName(path.filename().string());

    return texture;
}

}