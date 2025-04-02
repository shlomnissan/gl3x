// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

#include <filesystem>
#include <functional>
#include <memory>

namespace engine {

namespace fs = std::filesystem;

template <typename T>
using LoaderCallback = std::function<void(std::shared_ptr<T>)>;

class ENGINE_EXPORT Loader {
public:
    template<typename T>
    auto Load(const fs::path& path, LoaderCallback<T> callback) const -> void {
        auto resource = std::static_pointer_cast<T>(LoadImpl(path));
        callback(resource);
    }

    virtual ~Loader() = default;

protected:
    [[nodiscard]] virtual auto LoadImpl(const fs::path& path) const -> std::shared_ptr<void> = 0;

    [[nodiscard]] auto FileExists(const fs::path& path) const -> bool;
};

}