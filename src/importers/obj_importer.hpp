// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <filesystem>

#include "engine/nodes/node.hpp"

namespace engine::obj {

auto import_mesh(const std::filesystem::path& path) -> std::shared_ptr<Node>;

}