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

/**
 * @brief Loads 2D textures from engine-optimized `.tex` files.
 *
 * This class implements the abstract Loader interface to load Texture2D
 * resources from the file system, specifically targeting the engine's custom
 * `.tex` format. It supports both synchronous and asynchronous loading through
 * the base Loader API.
 *
 * You can convert standard image formats (e.g., PNG, JPG) into `.tex` files using the
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
 * auto MyNode::OnAttached(gleam::SharedContext* context) -> void override {
 *   context->Loaders().Texture->LoadAsync(
 *     "assets/my_texture.tex",
 *     [this](auto result) {
 *       if (result) {
 *         texture_ = result.value();
 *       } else {
 *         std::cerr << result.error() << '\n';
 *       }
 *      }
 *   );
 * }
 * @endcode
 *
 * @ingroup LoadersGroup
 */
class GLEAM_EXPORT TextureLoader : public Loader<Texture2D> {
public:
    /**
     * @brief Creates a shared pointer to a TextureLoader object.
     *
     * @return std::shared_ptr<TextureLoader>
     */
    [[nodiscard]] static auto Create() -> std::shared_ptr<TextureLoader> {
        return std::shared_ptr<TextureLoader>(new TextureLoader());
    }

private:
    /**
     * @brief Constructs a TextureLoader object.
     *
     * **Marked private** to enforce creation through the `Create()` factory method.
     */
    TextureLoader() = default;

    /**
     * @brief Loads 2D textures from engine-optimized `.tex` files.
     *
     * @param path File system path to the image file.
     * @return LoaderResult<Texture2D>
     */
    [[nodiscard]] auto LoadImpl(const fs::path& path) const -> LoaderResult<Texture2D> override;
};

}