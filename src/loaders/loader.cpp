// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "loaders/loader.hpp"

namespace engine {

auto Loader::FileExists(const fs::path& path) const -> bool {
    return fs::exists(path);
}

}