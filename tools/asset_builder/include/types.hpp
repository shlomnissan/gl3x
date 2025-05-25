// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <cstdint>

enum class TextureFormat : uint32_t {
    RGBA8 = 0
};

enum class VertexAttributeFlags : uint32_t {
    Position = 1 << 0,
    Normals = 1 << 1,
    UVs = 1 << 2,
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

#pragma pack(push, 1)
struct MeshHeader {
    char magic[4];
    uint32_t version;
    uint32_t header_size;
    uint32_t mesh_count;
    uint64_t file_size;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MeshEntryHeader {
    char name[64];
    uint32_t vertex_count;
    uint32_t index_count;
    uint32_t vertex_stride;
    uint32_t material_index;
    uint32_t vertex_flags;
    uint64_t vertex_data_size;
    uint64_t index_data_size;
};
#pragma pack(pop)