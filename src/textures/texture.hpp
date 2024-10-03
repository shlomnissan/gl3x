// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/math/utilities.hpp"

#include "core/disposable.hpp"

#include <string>

namespace engine {

class Texture : public Disposable {
public:
    [[nodiscard]]
    const auto& UUID() const { return uuid_; }

    virtual ~Texture() {
        Dispose();
    }

private:
    std::string uuid_ {math::GenerateUUID()};
};

}