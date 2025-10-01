/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include <expected>
#include <filesystem>
#include <functional>
#include <memory>
#include <string>
#include <thread>

namespace gleam {

namespace fs = std::filesystem;

template <typename T>
using LoaderResult = std::expected<std::shared_ptr<T>, std::string>;

template <typename T>
using LoaderCallback = std::function<void(LoaderResult<T>)>;

/**
 * @brief Abstract base class for resource loader types.
 *
 * Not intended for direct use.
 *
 * @ingroup LoadersGroup
 */
template <typename Resource>
class GLEAM_EXPORT Loader : public std::enable_shared_from_this<Loader<Resource>> {
public:
    /**
     * @brief Loads a resource synchronously from the specified file path. This
     * method verifies that the file exists before attempting to load.
     * If the file is missing or an error occurs during loading, an error
     * message is returned via `std::unexpected`.
     *
     * @param path File system path to the resource.
     * @return LoaderResult<Resource> Expected containing a shared pointer
     * to the loaded resource, or an error string.
     */
    auto Load(const fs::path& path) const -> LoaderResult<Resource> {
        if (!fs::exists(path)) {
            return std::unexpected("File not found '" + path.string() + "'");
        }
        return LoadImpl(path);
    }

    /**
     * @brief Loads a resource asynchronously from the specified file path.
     * The result is delivered to the provided callback on a background thread.
     * File existence is verified before loading. This implementation currently
     * spawns a detached thread and should be updated to use a thread pool
     * for better control and efficiency.
     *
     * @param path File system path to the resource.
     * @param callback Callback that receives the result of the loading operation.
     */
    auto LoadAsync(const fs::path& path, LoaderCallback<Resource> callback) const {
        if (!fs::exists(path)) {
            callback(std::unexpected("File not found '" + path.string() + "'"));
            return;
        }

        auto self = this->shared_from_this();
        std::thread([self, path, callback]() {
            auto result = self->LoadImpl(path);
            callback(result);
        }).detach();
    }

    /**
     * @brief Virtual destructor.
     */
    virtual ~Loader() = default;

private:
    /**
     * @brief Pure virtual method to implement the actual loading logic. Must
     * be overridden by derived classes to perform the resource-specific loading
     * process. The file is guaranteed to exist at this point.
     *
     * @param path File system path to the resource.
     * @return LoaderResult<Resource> Expected containing a shared pointer
     * to the loaded resource, or an error string.
     */
    [[nodiscard]] virtual auto LoadImpl(const fs::path& path) const -> LoaderResult<Resource> = 0;
};

}