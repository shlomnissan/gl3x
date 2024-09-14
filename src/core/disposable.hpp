// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

namespace engine {

class Disposable {
public:
    /**
     * @brief Disposes of resources associated with the derived object.
     *
     * This method iterates and invokes onDispose events to clean up resources.
     */
    auto Dispose() -> void;

    /**
     * @brief Checks if the derived object has been disposed.
     *
     * @return bool True if the object has been disposed, false otherwise.
     */
    [[nodiscard]] auto Disposed() const { return disposed_; }

    /**
     * @brief Destructor.
     */
    virtual ~Disposable() { Dispose(); }

private:
    /// @brief Flag indicating whether the object has been disposed.
    bool disposed_;
};

}