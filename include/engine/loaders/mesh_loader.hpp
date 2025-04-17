// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

#include "engine/nodes/mesh.hpp"

#include "loaders/loader.hpp"

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace engine {

using MeshCallback = std::function<void(std::shared_ptr<Mesh>)>;

class ENGINE_EXPORT MeshLoader : public Loader<Mesh> {
public:
    ~MeshLoader() override = default;

private:
    [[nodiscard]] auto ValidFileExtensions() const -> std::vector<std::string> override;

    [[nodiscard]] auto LoadImpl(const fs::path& path) const -> std::shared_ptr<void> override;
};

}