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

/**
 * @brief A class that provides a unique identifier and a name to nodes.
 */
class Identity {
public:
    /**
     * @brief Returns the unique identifier of the node.
     *
     * @return const std::string& The unique identifier of the node.
     */
    [[nodiscard]] const auto& UUID() const { return uuid_; }

    /**
     * @brief Returns the name of the node.
     *
     * @return const std::string& The name of the node.
     */
    [[nodiscard]] const auto& Name() const { return name_; }

    /**
     * @brief Sets the name of the node.
     *
     * @param name The name of the node.
     */
    auto SetName(std::string_view name) { name_ = name; }

private:
    /// @brief The unique identifier of the node.
    std::string uuid_ {math::GenerateUUID()};

    /// @brief The name of the node.
    std::string name_ {};
};

}