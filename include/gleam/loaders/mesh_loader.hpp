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

/**
 * @brief Loads mesh data from engine-optimized `.msh` files.
 *
 * This class implements the abstract Loader interface to load Mesh objects
 * from the file system, specifically targeting the engine's custom `.msh` format,
 * which encapsulates optimized mesh data along with associated materials.
 * It supports both synchronous and asynchronous loading through the base Loader API.
 *
 * This class returns an Node object, which serves as a group container
 * encapsulating one or more static Mesh objects.
 *
 * You can convert common 3D model formats (e.g., OBJ, FBX) into `.msh` files using the
 * `asset_builder` - a command-line tool located in the tools directory.
 *
 * Explicit instantiation of this class is discouraged due to potential
 * lifetime issues in the current architecture, particularly when used with
 * asynchronous loading. Instead, access it through the Node::OnAttached hook,
 * which provides a reference to the context that owns an instance of this class.
 *
 * @note Loaders use `std::expect` for error values. Always check that loading
 * operations return a valid result, and handle the error otherwise.
 *
 * @code
 * auto MyNode::OnAttached(SharedContextPointer context) -> void override {
 *   context->Loaders().Mesh->LoadAsync(
 *     "assets/my_model.msh",
 *     [this](auto result) {
 *       if (result) {
 *         this->Add(result.value());
 *       } else {
 *         std::println(stderr, "{}", result.error());
 *       }
 *     }
 *   );
 * }
 * @endcode
 *
 * @ingroup LoadersGroup
 */
class GLEAM_EXPORT MeshLoader : public Loader<Node> {
public:
    /**
     * @brief Creates a shared pointer to a MeshLoader object.
     *
     * @return std::shared_ptr<MeshLoader>
     */
    [[nodiscard]] static auto Create() -> std::shared_ptr<MeshLoader> {
        return std::shared_ptr<MeshLoader>(new MeshLoader());
    }

private:
    /**
     * @brief Constructs a MeshLoader object.
     *
     * **Marked private** to enforce creation through the `Create()` factory method.
     */
    MeshLoader() = default;

    /**
     * @brief Loads mesh data from engine-optimized `.msh` files.
     *
     * @param path File system path to the mesh file.
     * @return LoaderResult<Node>
     */
    [[nodiscard]] auto LoadImpl(const fs::path& path) const -> LoaderResult<Node> override;
};

}