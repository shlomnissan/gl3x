// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/loaders/texture_loader.hpp"

#include "utilities/logger.hpp"

#include <fstream>

#pragma pack(push, 1)
struct TextureHeader {
    char magic[4];
    uint32_t version;
    uint32_t width;
    uint32_t height;
    uint32_t format;
    uint32_t mip_levels;
    uint64_t pixel_data_size;
};
#pragma pack(pop)

namespace engine {

auto TextureLoader::ValidFileExtensions() const -> std::vector<std::string> {
    return {".tex"};
}

auto TextureLoader::LoadImpl(const fs::path& path) const -> std::shared_ptr<void> {
    auto file = std::ifstream {path, std::ios::binary};
    if (!file) {
        Logger::Log(LogLevel::Error, "Unabled to open file '{}'", path.string());
        return nullptr;
    }

    TextureHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    if (std::memcmp(header.magic, "TEX0", 4) != 0) {
        Logger::Log(LogLevel::Error, "Invalid texture file '{}'", path.string());
        return nullptr;
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