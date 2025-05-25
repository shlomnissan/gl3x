// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#define TINYOBJLOADER_IMPLEMENTATION

#include "mesh_converter.hpp"
#include "types.hpp"

#include <format>
#include <iostream>
#include <vector>

#include "tiny_obj_loader.hpp"

auto convert_mesh(
    const fs::path& input_path,
    const fs::path& output_path
) -> std::expected<void, std::string> {
    auto reader_config = tinyobj::ObjReaderConfig {};
    auto reader = tinyobj::ObjReader {};

    if (!reader.ParseFromFile(input_path.string(), reader_config)) {
        return reader.Error().empty() ?
            std::unexpected(std::format("Error: Failed to load mesh {}\n", input_path.string())) :
            std::unexpected(std::format("Error: {}\n", reader.Error()));
    }

    if (!reader.Warning().empty()) {
        std::cout << std::format("Warning: {}\n", reader.Warning());
    }

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();

    auto header = MeshHeader {};
    std::memcpy(header.magic, "MES0", 4);
    header.version = 1;
    header.header_size = sizeof(MeshHeader);
    header.mesh_count = static_cast<uint32_t>(shapes.size());

    auto out_stream = std::ofstream {output_path, std::ios::binary};
    if (!out_stream) {
        return std::unexpected("Failed to open output file: " + output_path.string());
    }

    out_stream.write(reinterpret_cast<const char*>(&header), sizeof(header));

    return {};
}