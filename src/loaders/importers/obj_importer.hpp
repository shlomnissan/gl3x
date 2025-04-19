// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <filesystem>

#include "engine/nodes/mesh.hpp"

namespace engine::obj {

auto import(const std::filesystem::path& path) -> std::shared_ptr<Mesh>;

}