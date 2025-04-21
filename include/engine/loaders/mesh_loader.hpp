// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

#include "loaders/loader.hpp"

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace engine {

class Mesh;

namespace fs = std::filesystem;

using MeshCallback = std::function<void(std::shared_ptr<Mesh>)>;

class ENGINE_EXPORT MeshLoader : public Loader<Mesh> {
public:
    [[nodiscard]] static auto Create() -> std::shared_ptr<MeshLoader> {
        return std::shared_ptr<MeshLoader>(new MeshLoader());
    }

    ~MeshLoader() override = default;

private:
    MeshLoader() = default;

    [[nodiscard]] auto ValidFileExtensions() const -> std::vector<std::string> override;

    [[nodiscard]] auto LoadImpl(const fs::path& path) const -> std::shared_ptr<void> override;
};

}