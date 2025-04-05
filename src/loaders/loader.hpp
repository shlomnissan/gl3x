// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

#include "utilities/logger.hpp"

#include <filesystem>
#include <functional>
#include <memory>
#include <ranges>
#include <string>
#include <thread>
#include <vector>

namespace engine {

namespace fs = std::filesystem;

template <typename T>
using LoaderCallback = std::function<void(std::shared_ptr<T>)>;

template<typename Resource>
class ENGINE_EXPORT Loader {
public:
    auto Load(const fs::path& path, LoaderCallback<Resource> callback) const -> void {
        if (!FileSupported(path) || !FileExists(path)) return;

        auto resource = std::static_pointer_cast<Resource>(LoadImpl(path));
        if (resource) {
            callback(resource);
        } else {
            Logger::Log(LogLevel::Error, "Failed to load resource '{}'", path.string());
        }
    }

    auto LoadAsync(const fs::path& path, LoaderCallback<Resource> callback) const -> void {
        if (!FileSupported(path) || !FileExists(path)) return;

        // TODO: Use a thread pool instead of creating a thread and detaching it.
        std::thread([this, path, callback]() {
            auto resource = std::static_pointer_cast<Resource>(LoadImpl(path));
            if (resource) {
                callback(resource);
            } else {
                Logger::Log(LogLevel::Error, "Failed to load resource async '{}'", path.string());
            }
        }).detach();
    }

    virtual ~Loader() = default;

protected:
    [[nodiscard]] virtual auto ValidFileExtensions() const -> std::vector<std::string> = 0;

    [[nodiscard]] virtual auto LoadImpl(const fs::path& path) const -> std::shared_ptr<void> = 0;

private:
    auto FileSupported(const fs::path& path) const {
        const auto ext = path.extension().string();

        if (std::ranges::any_of(ValidFileExtensions(), [&ext](const auto& valid_ext)
            { return ext == valid_ext; })) { return true; }

        Logger::Log(LogLevel::Error, "Unsupported file type '{}'", ext);
        return false;
    }

    auto FileExists(const fs::path& path) const {
        if (!fs::exists(path)) {
            Logger::Log(LogLevel::Error, "File not found '{}'", path.string());
            return false;
        }
        return true;
    }
};

}