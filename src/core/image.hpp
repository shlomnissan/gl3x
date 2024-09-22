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
    ImageDataPtr data_;

    unsigned int width_;
    unsigned int height_;
    unsigned int depth_;
};

}