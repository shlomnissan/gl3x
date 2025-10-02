/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <functional>
#include <vector>

namespace gleam {

/// @cond INTERNAL
class Disposable {
public:
    using OnDisposeCallback = std::function<void(Disposable*)>;

    Disposable() = default;

    // delete copy constructor and assignment operator
    Disposable(const Disposable&) = delete;
    auto operator=(const Disposable&) -> Disposable& = delete;

    // delete move constructor and assignment operator
    Disposable(Disposable&&) = delete;
    auto operator=(Disposable&&) -> Disposable& = delete;

    virtual auto Dispose() -> void {
        if (!disposed_) {
            disposed_ = true;
            for (const auto& c : dispose_callbacks_) c(this);
        }
    }

    [[nodiscard]] virtual auto Disposed() -> bool { return disposed_; }

    auto OnDispose(const OnDisposeCallback& callback) {
        dispose_callbacks_.emplace_back(callback);
    }

    virtual ~Disposable() = default;

private:
    std::vector<OnDisposeCallback> dispose_callbacks_;

    bool disposed_ {false};
};
/// @endcond

}