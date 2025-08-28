/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam/math/utilities.hpp"

#include <string>
#include <string_view>

namespace gleam {

/// @cond INTERNAL
class Identity {
public:
    [[nodiscard]] const auto& UUID() const { return uuid_; }

    [[nodiscard]] const auto& Name() const { return name_; }

    auto SetName(std::string_view name) { name_ = name; }

private:
    std::string uuid_ {math::GenerateUUID()};

    std::string name_ {};
};
/// @endcond

}