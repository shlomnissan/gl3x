// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "core/logger.hpp"

#include <string>
#include <memory>
#include <fmt/format.h>

namespace engine {

using ImageDataPtr = std::unique_ptr<unsigned char[], void(*)(void*)>;

class Image {
public:
    struct ImageMetadata {
        std::string filename;
        unsigned int width;
        unsigned int height;
        unsigned int depth;
    };

    Image() = default;

    Image(const ImageMetadata& params, ImageDataPtr data) :
      data_(std::move(data)),
      filename_(params.filename),
      width_(params.width),
      height_(params.height),
      depth_(params.depth) {
        LogInfo(fmt::format("Image loaded '{}'", filename_));
    }

    Image(Image&& other) noexcept :
      data_(std::move(other.data_)),
      filename_(std::move(other.filename_)),
      width_(other.width_),
      height_(other.height_),
      depth_(other.depth_) {
        Reset(other);
    }

    auto operator=(Image&& other) noexcept -> Image& {
        if (this != &other) {
            Free();

            data_ = std::move(other.data_);
            filename_ = std::move(other.filename_);
            width_ = other.width_;
            height_ = other.height_;
            depth_ = other.depth_;

            Reset(other);
        }
        return *this;
    }

    [[nodiscard]] auto Data() const { return data_.get(); }

    [[nodiscard]] auto Width() const { return width_; }

    [[nodiscard]] auto Height() const { return height_; }

    [[nodiscard]] auto Depth() const { return depth_; }

    auto Free() -> void {
        if (data_ != nullptr) {
            data_.reset();
            LogInfo(fmt::format("Image memory cleared '{}'", filename_));
        }
        Reset(*this);
    }

    ~Image() {
        Free();
    }

private:
    ImageDataPtr data_ {nullptr, [](void*){}};

    std::string filename_ {};
    unsigned int width_ {0};
    unsigned int height_ {0};
    unsigned int depth_ {0};

    auto Reset(Image& instance) -> void {
        instance.data_ = nullptr;
        instance.filename_.clear();
        instance.width_ = 0;
        instance.height_ = 0;
        instance.depth_ = 0;
    }
};

}