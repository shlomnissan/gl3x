// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "gleam_export.h"

#include "loaders/loader.hpp"

#include <expected>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace engine {

class Node;

namespace fs = std::filesystem;

using MeshCallback = std::function<void(std::shared_ptr<Node>)>;

class GLEAM_EXPORT MeshLoader : public Loader<Node> {
public:
    [[nodiscard]] static auto Create() -> std::shared_ptr<MeshLoader> {
        return std::shared_ptr<MeshLoader>(new MeshLoader());
    }

    ~MeshLoader() override = default;

private:
    MeshLoader() = default;

    [[nodiscard]] auto LoadImpl(const fs::path& path) const -> LoaderResult<Node> override;
};

}