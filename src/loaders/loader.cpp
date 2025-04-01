// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "loaders/loader.hpp"

namespace engine {

Loader::Loader(const fs::path& path) : path_(path) {}

auto Loader::FileExists(const fs::path& path) const -> bool {
    return fs::exists(path);
}

}