/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include <cmath>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>

namespace gleam::math {

constexpr float pi = 3.1415926535897932384626433832795f;
constexpr float half_pi = 1.5707963267948966192313216916398f;
constexpr float two_pi = 6.2831853071795864769252867665590f;
constexpr float epsilon = 1e-6f;

[[nodiscard]] constexpr auto DegToRad(const float degrees) {
    return degrees * (pi / 180.0f);
}

[[nodiscard]] constexpr auto RadToDeg(const float radians) {
    return radians * (180.0f / pi);
}

[[nodiscard]] constexpr auto Lerp(const float a, const float b, const float f) {
    return std::lerp(a, b, f);
}

constexpr auto CantorPairing(const auto x, const auto y) {
    return ((x + y) * (x + y + 1)) / 2 + y;
}

constexpr auto UnorderedCantorPairing(const auto x, const auto y) {
    return x > y ? CantorPairing(y, x) : CantorPairing(x, y);
}

[[nodiscard]] GLEAM_EXPORT inline auto GenerateUUID() {
    static std::vector<std::string> lut{
        "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0a",
        "0b", "0c", "0d", "0e", "0f", "10", "11", "12", "13", "14", "15",
        "16", "17", "18", "19", "1a", "1b", "1c", "1d", "1e", "1f", "20",
        "21", "22", "23", "24", "25", "26", "27", "28", "29", "2a", "2b",
        "2c", "2d", "2e", "2f", "30", "31", "32", "33", "34", "35", "36",
        "37", "38", "39", "3a", "3b", "3c", "3d", "3e", "3f", "40", "41",
        "42", "43", "44", "45", "46", "47", "48", "49", "4a", "4b", "4c",
        "4d", "4e", "4f", "50", "51", "52", "53", "54", "55", "56", "57",
        "58", "59", "5a", "5b", "5c", "5d", "5e", "5f", "60", "61", "62",
        "63", "64", "65", "66", "67", "68", "69", "6a", "6b", "6c", "6d",
        "6e", "6f", "70", "71", "72", "73", "74", "75", "76", "77", "78",
        "79", "7a", "7b", "7c", "7d", "7e", "7f", "80", "81", "82", "83",
        "84", "85", "86", "87", "88", "89", "8a", "8b", "8c", "8d", "8e",
        "8f", "90", "91", "92", "93", "94", "95", "96", "97", "98", "99",
        "9a", "9b", "9c", "9d", "9e", "9f", "a0", "a1", "a2", "a3", "a4",
        "a5", "a6", "a7", "a8", "a9", "aa", "ab", "ac", "ad", "ae", "af",
        "b0", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9", "ba",
        "bb", "bc", "bd", "be", "bf", "c0", "c1", "c2", "c3", "c4", "c5",
        "c6", "c7", "c8", "c9", "ca", "cb", "cc", "cd", "ce", "cf", "d0",
        "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9", "da", "db",
        "dc", "dd", "de", "df", "e0", "e1", "e2", "e3", "e4", "e5", "e6",
        "e7", "e8", "e9", "ea", "eb", "ec", "ed", "ee", "ef", "f0", "f1",
        "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "fa", "fb", "fc",
        "fd", "fe", "ff"
    };

    static std::random_device rd;
    static std::mt19937 e2(rd());
    static std::uniform_real_distribution dist(0.0, 1.0);

    const auto d0 = static_cast<size_t>(dist(e2) * 0xffffffff) | 0;
    const auto d1 = static_cast<size_t>(dist(e2) * 0xffffffff) | 0;
    const auto d2 = static_cast<size_t>(dist(e2) * 0xffffffff) | 0;
    const auto d3 = static_cast<size_t>(dist(e2) * 0xffffffff) | 0;

    auto uuid = lut[d0 & 0xff] + lut[d0 >> 8 & 0xff] + lut[d0 >> 16 & 0xff] +
                lut[d0 >> 24 & 0xff] + '-' + lut[d1 & 0xff] +
                lut[d1 >> 8 & 0xff]  + '-' + lut[d1 >> 16 & 0x0f | 0x40] +
                lut[d1 >> 24 & 0xff] + '-' + lut[d2 & 0x3f | 0x80] +
                lut[d2 >> 8 & 0xff]  + '-' + lut[d2 >> 16 & 0xff] +
                lut[d2 >> 24 & 0xff] + lut[d3 & 0xff] + lut[d3 >> 8 & 0xff] +
                lut[d3 >> 16 & 0xff] + lut[d3 >> 24 & 0xff];

    return uuid;
}

}