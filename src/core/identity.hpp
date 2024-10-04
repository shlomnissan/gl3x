// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/math/utilities.hpp"

#include <string>

namespace engine {

class Identity {
public:
    [[nodiscard]] const auto& UUID() const { return uuid_; }

private:
    std::string uuid_ {math::GenerateUUID()};
};

}