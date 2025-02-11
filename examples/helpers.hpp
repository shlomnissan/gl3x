// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <format>
#include <string_view>

#include <imgui.h>

static auto UISliderFloat(
    std::string_view label,
    float& value,
    float min,
    float max,
    bool& dirty,
    float width = 120.0f)
{
    ImGui::SetNextItemWidth(width);
    if (ImGui::SliderFloat(std::format("{}", label).c_str(), &value, min, max)) {
        dirty = true;
    }
}

static auto UISliderUnsigned(
    std::string_view label,
    unsigned& value,
    unsigned min,
    unsigned max,
    bool& dirty,
    float width = 120.0f)
{
    auto v = static_cast<int>(value);
    ImGui::SetNextItemWidth(width);
    if (ImGui::SliderInt(std::format("{}", label).c_str(), &v, min, max)) {
        value = static_cast<unsigned>(v);
        dirty = true;
    }
}