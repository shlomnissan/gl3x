// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/core/image.hpp"

#include "utilities/logger.hpp"

namespace engine {

Image::Image(const ImageMetadata& params, ImageDataPtr data) :
  data_(std::move(data)),
  filename_(params.filename),
  width_(params.width),
  height_(params.height),
  depth_(params.depth) {
    Logger::Log(LogLevel::Info, "Image loaded '{}'", filename_);
}

Image::Image(Image&& other) noexcept :
  data_(std::move(other.data_)),
  filename_(std::move(other.filename_)),
  width_(other.width_),
  height_(other.height_),
  depth_(other.depth_) {
    Reset(other);
}

auto Image::operator=(Image&& other) noexcept -> Image& {
    if (this != &other) {
        data_ = std::move(other.data_);
        filename_ = std::move(other.filename_);
        width_ = other.width_;
        height_ = other.height_;
        depth_ = other.depth_;
        Reset(other);
    }
    return *this;
}

auto Image::Dispose() -> void {
    if (data_ != nullptr) {
        data_.reset();
        Logger::Log(LogLevel::Info, "Image memory cleared '{}'", filename_);
        Disposable::Dispose();
    }
    Reset(*this);
}

auto Image::Reset(Image& instance) const -> void {
    instance.data_ = nullptr;
    instance.filename_.clear();
    instance.width_ = 0;
    instance.height_ = 0;
    instance.depth_ = 0;
}

}