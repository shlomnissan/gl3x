// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

#include "engine/core/image.hpp"

#include "loaders/loader.hpp"

namespace engine {

using ImageCallback = std::function<void(std::shared_ptr<Image>)>;

class ENGINE_EXPORT ImageLoader : public Loader {
public:
    auto Load(const fs::path& path, const ImageCallback& callback) const -> void;

    ~ImageLoader() override = default;

private:
    [[nodiscard]] auto LoadImpl(const fs::path& path) const -> std::shared_ptr<void> override;
};

}