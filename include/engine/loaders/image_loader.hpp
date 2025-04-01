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
    explicit ImageLoader(const fs::path& path);

    ~ImageLoader() override = default;

    auto Load(const ImageCallback& callback) const -> void;

private:
    [[nodiscard]] auto LoadImpl() const -> std::shared_ptr<void> override;
};

}