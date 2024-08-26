// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/scene/node.hpp"

namespace engine {

/**
 * @brief Represents the scene's root node.
 */
class ENGINE_EXPORT Scene : public Node {
public:
    /**
     * @brief Creates a new instance of the Scene class.
     *
     * @return A `std::shared_ptr<Scene>` pointing to the newly created Scene instance.
     */
    static auto Create() {
        return std::make_shared<Scene>();
    }
};

}