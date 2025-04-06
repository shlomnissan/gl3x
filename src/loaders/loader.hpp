// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

#include "utilities/logger.hpp"

#include <algorithm>
#include <expected>
#include <filesystem>
#include <format>
#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace engine {

namespace fs = std::filesystem;

template <typename T>
using LoaderResult = std::expected<std::shared_ptr<T>, std::string>;

template <typename T>
using LoaderCallback = std::function<void(LoaderResult<T>)>;

template <typename Resource>
class ENGINE_EXPORT Loader {
public:
    auto Load(const fs::path& path, LoaderCallback<Resource> callback) const {
        if (!ValidateFile(path, callback)) return;

        auto resource = std::static_pointer_cast<Resource>(LoadImpl(path));
        if (resource) {
            callback(resource);
        } else {
            const auto message = std::format("Failed to load resource '{}'", path.string());
            Logger::Log(LogLevel::Error, message);
            callback(std::unexpected(message));
        }
    }

    // TODO: Use a thread pool instead of creating a thread and detaching it.
    auto LoadAsync(const fs::path& path, LoaderCallback<Resource> callback) const {
        std::thread([this, path, callback]() {
            if (!ValidateFile(path, callback)) return;
            auto resource = std::static_pointer_cast<Resource>(LoadImpl(path));
            if (resource) {
                callback(resource);
            } else {
                const auto message = std::format("Failed to load resource '{}'", path.string());
                Logger::Log(LogLevel::Error, message);
                callback(std::unexpected(message));
            }
        }).detach();
    }

    virtual ~Loader() = default;

protected:
    [[nodiscard]] virtual auto ValidFileExtensions() const -> std::vector<std::string> = 0;

    [[nodiscard]] virtual auto LoadImpl(const fs::path& path) const -> std::shared_ptr<void> = 0;

private:
    auto ValidateFile(const fs::path& path, LoaderCallback<Resource> callback) const {
        if (!ValidateFileType(path)) {
            const auto& str = path.extension().string();
            const auto message = std::format("Unsupported file type '{}'", str);
            Logger::Log(LogLevel::Error, message);
            callback(std::unexpected(message));
            return false;
        }

        if (!fs::exists(path)) {
            const auto& str = path.string();
            const auto message = std::format("File not found '{}'", str);
            Logger::Log(LogLevel::Error, message);
            callback(std::unexpected(message));
            return false;
        }

        return true;
    }

    auto ValidateFileType(const fs::path& path) const {
        return std::ranges::any_of(ValidFileExtensions(),
            [ext = path.extension().string()](const auto& v) {
                return ext == v;
            }
        );
    }
};

}