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
class ENGINE_EXPORT Loader : public std::enable_shared_from_this<Loader<Resource>> {
public:
    auto Load(const fs::path& path, LoaderCallback<Resource> callback) const {
        if (!ValidateFile(path, callback)) return;

        auto result = LoadImpl(path);
        if (result) {
            callback(std::static_pointer_cast<Resource>(result.value()));
        } else {
            Logger::Log(LogLevel::Error, result.error());
            callback(std::unexpected(result.error()));
        }
    }

    // TODO: Use a thread pool instead of creating a thread and detaching it.
    auto LoadAsync(const fs::path& path, LoaderCallback<Resource> callback) const {
        if (!ValidateFile(path, callback)) return;

        auto self = this->shared_from_this();
        std::thread([self, path, callback]() {
            auto result = self->LoadImpl(path);
            if (result) {
                callback(std::static_pointer_cast<Resource>(result.value()));
            } else {
                Logger::Log(LogLevel::Error, result.error());
                callback(std::unexpected(result.error()));
            }
        }).detach();
    }

    virtual ~Loader() = default;

protected:
    [[nodiscard]] virtual auto LoadImpl(const fs::path& path) const -> std::expected<std::shared_ptr<void>, std::string> = 0;

private:
    auto ValidateFile(const fs::path& path, LoaderCallback<Resource> callback) const {
        if (!fs::exists(path)) {
            const auto& str = path.string();
            const auto message = std::format("File not found '{}'", str);
            Logger::Log(LogLevel::Error, message);
            callback(std::unexpected(message));
            return false;
        }

        return true;
    }
};

}