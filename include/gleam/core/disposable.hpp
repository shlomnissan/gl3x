// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <functional>
#include <vector>

namespace gleam {

/**
 * @brief Base class for objects that require manual disposal.
 */
class Disposable {
public:
    using OnDisposeCallback = std::function<void(Disposable*)>;

    /// @brief Default constructor.
    Disposable() = default;
    /// @brief Deleted copy constructor.
    Disposable(const Disposable&) = delete;
    /// @brief Deleted move constructor.
    Disposable(Disposable&&) = delete;
    /// @brief Deleted copy assignment operator.
    auto operator=(const Disposable&) -> Disposable& = delete;
    /// @brief Deleted move assignment operator.
    auto operator=(Disposable&&) -> Disposable& = delete;

    /**
     * @brief Disposes the object and invokes all registered dispose callbacks.
     */
    virtual auto Dispose() -> void {
        if (!disposed_) {
            disposed_ = true;
            for (const auto& c : dispose_callbacks_) c(this);
        }
    }

    /**
     * @brief Checks if the object has been disposed.
     *
     * @return `true` if the object has been disposed, `false` otherwise.
     */
    [[nodiscard]] virtual auto Disposed() -> bool { return disposed_; }

    /**
     * @brief Registers a callback to be invoked when the object is disposed.
     *
     * @param callback The callback to be invoked.
     */
    auto OnDispose(const OnDisposeCallback& callback) {
        dispose_callbacks_.emplace_back(callback);
    }

    /**
     * @brief Default virtual destructor.
     */
    virtual ~Disposable() = default;

protected:
    /// @brief Flag indicating whether the object has been disposed.
    bool disposed_ {false};

private:
    /// @brief List of callbacks to be invoked when the object is disposed.
    std::vector<OnDisposeCallback> dispose_callbacks_;
};

}