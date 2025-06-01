// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <type_traits>

namespace gleam {

template <typename T>
std::enable_if_t<std::is_trivially_copyable_v<T>>
read_binary(std::istream& in, T& value) {
    in.read(reinterpret_cast<char*>(&value), sizeof(T));
}

template <typename T>
std::enable_if_t<std::is_trivially_copyable_v<T>>
read_binary(std::istream& in, std::vector<T>& vec, std::size_t count) {
    in.read(reinterpret_cast<char*>(vec.data()), count);
}

}