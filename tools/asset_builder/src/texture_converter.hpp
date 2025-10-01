/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <expected>
#include <filesystem>

namespace fs = std::filesystem;

auto convert_texture(
    const fs::path& input_path,
    const fs::path& output_path
) -> std::expected<void, std::string>;