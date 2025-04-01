// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

#include "utilities/logger.hpp"

#include <filesystem>
#include <functional>
#include <memory>

namespace engine {

namespace fs = std::filesystem;

class ENGINE_EXPORT Loader {
public:
    explicit Loader(const fs::path& path);

    virtual ~Loader() = default;

    template<typename T>
    auto Load(std::function<void(std::shared_ptr<T>)> callback) const -> void {
        auto resource = std::static_pointer_cast<T>(LoadImpl());
        callback(resource);
    }

protected:
    fs::path path_;

    [[nodiscard]] virtual auto LoadImpl() const -> std::shared_ptr<void> = 0;

    [[nodiscard]] auto FileExists(const fs::path& path) const -> bool;
};

}