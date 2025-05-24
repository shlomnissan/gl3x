// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#define STB_IMAGE_IMPLEMENTATION

#include "texture_converter.hpp"

#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>

#include "stb_image/stb_image.hpp"

enum class TextureFormat : uint32_t {
    RGBA8_UNORM = 0
};

#pragma pack(push, 1)
struct TextureHeader {
    char magic[4];
    uint32_t version;
    uint32_t header_size;
    uint32_t width;
    uint32_t height;
    uint32_t format;
    uint32_t mip_levels;
    uint64_t pixel_data_size;
};
#pragma pack(pop)

auto convert_texture(
    const fs::path& input_path,
    const fs::path& output_path
) -> std::expected<void, std::string> {
    auto width = 0;
    auto height = 0;
    auto channels = 0;

    stbi_set_flip_vertically_on_load(true);
    auto data = stbi_load(input_path.string().c_str(), &width, &height, &channels, 4);
    if (!data) {
        return std::unexpected("Failed to load image: " + input_path.string());
    }

    auto header = TextureHeader {};
    std::memcpy(header.magic, "TEX0", 4);
    header.version = 1;
    header.header_size = sizeof(TextureHeader);
    header.width = static_cast<uint32_t>(width);
    header.height = static_cast<uint32_t>(height);
    header.format = static_cast<uint32_t>(TextureFormat::RGBA8_UNORM);
    header.mip_levels = 1;
    header.pixel_data_size = static_cast<uint64_t>(width) * height * 4;

    auto out_stream = std::ofstream {output_path, std::ios::binary};
    if (!out_stream) {
        stbi_image_free(data);
        return std::unexpected("Failed to open output file: " + output_path.string());
    }

    out_stream.write(reinterpret_cast<const char*>(&header), sizeof(header));
    out_stream.write(reinterpret_cast<const char*>(data), header.pixel_data_size);
    stbi_image_free(data);

    return {};
}