// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include <functional>
#include <string>
#include <string_view>

namespace engine {

class ENGINE_EXPORT Window {
public:
    explicit Window(std::string_view title);

    Window(std::string_view title, int width, int height);

    auto Tick(const std::function<void(const double delta)>& tick) -> void;

private:
    int width_ = 800;
    int height_ = 600;

    std::string title_;
};

}