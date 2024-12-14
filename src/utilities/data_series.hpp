// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <concepts>
#include <limits>

template <typename T, size_t N>
requires std::is_arithmetic_v<T>
class DataSeries {
public:
    static_assert(N > 0, "DataSeries buffer size must be greater than 0");

    // min and max are used to keep track of the min and max values that were
    // added to the buffer. it's possible that the min and max values are not
    // currently in the buffer, but they were at some point. this is useful for
    // calculating the range of values of the buffer.
    T min_value {std::numeric_limits<T>::max()};
    T max_value {std::numeric_limits<T>::min()};
    T last_value {0};
    bool has_values {false};

    auto Push(const T value) {
        has_values = true;

        sum_ += value - buffer_[idx_];
        buffer_[idx_] = value;
        idx_ = (idx_ + 1) % N;

        last_value = value;
        count_ = std::min(count_ + 1, N);
        min_value = std::min(min_value, value);
        max_value = std::max(max_value, value);
    }

    [[nodiscard]] auto Average() const {
        return count_ > 0 ? sum_ / count_ : T {};
    }

    [[nodiscard]] auto Buffer() const {
        return buffer_.data();
    }

private:
    std::array<T, N> buffer_ {};

    T sum_ {0};

    size_t count_ {0};
    size_t idx_ {0};
};