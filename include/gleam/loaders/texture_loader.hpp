// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "gleam_export.h"

#include "gleam/textures/texture_2d.hpp"

#include "loaders/loader.hpp"

#include <expected>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace gleam {

namespace fs = std::filesystem;

using TextureCallback = std::function<void(std::shared_ptr<Texture2D>)>;

class GLEAM_EXPORT TextureLoader : public Loader<Texture2D> {
public:
    [[nodiscard]] static auto Create() -> std::shared_ptr<TextureLoader> {
        return std::shared_ptr<TextureLoader>(new TextureLoader());
    }

    ~TextureLoader() override = default;

private:
    TextureLoader() = default;

    [[nodiscard]] auto LoadImpl(const fs::path& path) const -> LoaderResult<Texture2D> override;
};

}