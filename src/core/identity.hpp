// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/math/utilities.hpp"

#include <string>
#include <string_view>

namespace engine {

class Identity {
public:
    [[nodiscard]] const auto& UUID() const { return uuid_; }

    [[nodiscard]] const auto& Name() const { return name_; }

    auto SetName(std::string_view name) { name_ = name; }

private:
    std::string uuid_ {math::GenerateUUID()};

    std::string name_ {};
};

}