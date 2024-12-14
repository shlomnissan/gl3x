// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <concepts>

template <typename T, size_t N>
requires std::is_arithmetic_v<T>
class DataSeries {
public:
    static_assert(N > 0, "DataSeries buffer size must be greater than 0");

    auto Push(const T value) {
        if (count_ < N) {
            buffer_[count_++] = value;
        } else {
            sum_ -= buffer_[0];
            std::rotate(buffer_.begin(), buffer_.begin() + 1, buffer_.end());
            buffer_[N - 1] = value;
        }
        sum_ += value;
    }

    [[nodiscard]] auto LastValue() const {
        return count_ > 0 ? buffer_[count_ - 1] : T {};
    }

    [[nodiscard]] auto Average() const {
        return count_ > 0 ? sum_ / count_ : T {};
    }

    [[nodiscard]] auto Buffer() const -> const T* {
        return buffer_.data();
    }

private:
    std::array<T, N> buffer_ {};

    T sum_ {0};

    size_t count_ {0};
};