/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <expected>
#include <filesystem>

namespace fs = std::filesystem;

auto convert_mesh(
    const fs::path& input_path,
    const fs::path& output_path
) -> std::expected<void, std::string>;