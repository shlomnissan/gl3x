// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/disposable.hpp"

namespace engine {

auto Disposable::Dispose() -> void {
    disposed_ = true;
    // TODO: dispatch events
}

}