// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <functional>
#include <vector>

namespace engine {

class Disposable;
using OnDisposeCallback = std::function<void(Disposable*)>;

class Disposable {
public:
    Disposable() = default;

    Disposable(const Disposable&) = delete;
    Disposable(Disposable&&) = delete;
    auto operator=(const Disposable&) -> Disposable& = delete;
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

protected:
    bool disposed_ {false};

private:
    std::vector<OnDisposeCallback> dispose_callbacks_;
};

}