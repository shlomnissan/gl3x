// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/core/image.hpp"

#include "utilities/logger.hpp"

namespace engine {

Image::Image(const ImageMetadata& params, ImageData data) :
    filename(params.filename),
    width(params.width),
    height(params.height),
    depth(params.depth),
    data_(std::move(data))
{
    Logger::Log(LogLevel::Info, "Image loaded '{}'", filename);
}

Image::Image(Image&& other) noexcept :
    filename(std::move(other.filename)),
    width(other.width),
    height(other.height),
    depth(other.depth),
    data_(std::move(other.data_))
{
    Reset(other);
}

auto Image::operator=(Image&& other) noexcept -> Image& {
    if (this != &other) {
        data_ = std::move(other.data_);
        filename = std::move(other.filename);
        width = other.width;
        height = other.height;
        depth = other.depth;
        Reset(other);
    }
    return *this;
}

auto Image::Dispose() -> void {
    if (data_ != nullptr) {
        data_.reset();
        Logger::Log(LogLevel::Info, "Image memory cleared '{}'", filename);
        Disposable::Dispose();
    }
    Reset(*this);
}

auto Image::Reset(Image& instance) const -> void {
    instance.data_ = nullptr;
    instance.filename.clear();
    instance.width = 0;
    instance.height = 0;
    instance.depth = 0;
}

}