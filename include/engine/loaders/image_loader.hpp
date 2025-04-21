// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

#include "engine/core/image.hpp"

#include "loaders/loader.hpp"

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace engine {

namespace fs = std::filesystem;

using ImageCallback = std::function<void(std::shared_ptr<Image>)>;

class ENGINE_EXPORT ImageLoader : public Loader<Image> {
public:
    bool flip_y {true};

    [[nodiscard]] static auto Create() -> std::shared_ptr<ImageLoader> {
        return std::shared_ptr<ImageLoader>(new ImageLoader());
    }

    ~ImageLoader() override = default;

private:
    ImageLoader() = default;

    [[nodiscard]] auto ValidFileExtensions() const -> std::vector<std::string> override;

    [[nodiscard]] auto LoadImpl(const fs::path& path) const -> std::shared_ptr<void> override;
};

}