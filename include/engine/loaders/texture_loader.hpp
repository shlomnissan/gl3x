// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

#include "engine/textures/texture_2d.hpp"

#include "loaders/loader.hpp"

#include <expected>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace engine {

namespace fs = std::filesystem;

using TextureCallback = std::function<void(std::shared_ptr<Texture2D>)>;

class ENGINE_EXPORT TextureLoader : public Loader<Texture2D> {
public:
    [[nodiscard]] static auto Create() -> std::shared_ptr<TextureLoader> {
        return std::shared_ptr<TextureLoader>(new TextureLoader());
    }

    ~TextureLoader() override = default;

private:
    TextureLoader() = default;

    [[nodiscard]] auto LoadImpl(const fs::path& path) const -> std::expected<std::shared_ptr<void>, std::string> override;
};

}