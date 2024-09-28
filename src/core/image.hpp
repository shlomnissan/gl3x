// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <memory>

namespace engine {

using ImageDataPtr = std::unique_ptr<unsigned char[], void(*)(void*)>;

class Image {
public:
    struct ImageMetadata {
        unsigned int width;
        unsigned int height;
        unsigned int depth;
    };

    Image() = default;

    Image(const ImageMetadata& params, ImageDataPtr data) :
        data_(std::move(data)),
        width_(params.width),
        height_(params.height),
        depth_(params.depth) {}

    [[nodiscard]] auto Data() const { return data_.get(); }

    [[nodiscard]] auto Width() const { return width_; }

    [[nodiscard]] auto Height() const { return height_; }

    [[nodiscard]] auto Depth() const { return depth_; }

private:
    ImageDataPtr data_ {nullptr, [](void*){}};

    unsigned int width_ {0};
    unsigned int height_ {0};
    unsigned int depth_ {0};
};

}