/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/loaders/loader.hpp"
#include "gleam/textures/texture_2d.hpp"

#include <filesystem>
#include <memory>

namespace gleam {

namespace fs = std::filesystem;

using TextureCallback = std::function<void(std::shared_ptr<Texture2D>)>;

class GLEAM_EXPORT TextureLoader : public Loader<Texture2D> {
public:
    [[nodiscard]] static auto Create() -> std::shared_ptr<TextureLoader> {
        return std::shared_ptr<TextureLoader>(new TextureLoader());
    }

private:
    TextureLoader() = default;

    [[nodiscard]] auto LoadImpl(const fs::path& path) const -> LoaderResult<Texture2D> override;
};

}