/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/loaders/loader.hpp"

#include <filesystem>
#include <memory>

namespace gleam {

class Node;

namespace fs = std::filesystem;

using MeshCallback = std::function<void(std::shared_ptr<Node>)>;

class GLEAM_EXPORT MeshLoader : public Loader<Node> {
public:
    [[nodiscard]] static auto Create() -> std::shared_ptr<MeshLoader> {
        return std::shared_ptr<MeshLoader>(new MeshLoader());
    }

private:
    MeshLoader() = default;

    [[nodiscard]] auto LoadImpl(const fs::path& path) const -> LoaderResult<Node> override;
};

}