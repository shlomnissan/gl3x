// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <format>
#include <string>

using Label = const std::string&;

auto UISeparator() -> void;

auto UIText(Label text) -> void;

auto UISliderFloat(Label label, float& value, float min, float max, bool& dirty, float width = 120.0f) -> void;

auto UISliderUnsigned(Label label, unsigned& value, unsigned min, unsigned max, bool& dirty, float width = 120.0f) -> void;

auto UICheckbox(Label label, bool& value, bool& dirty, float offset = 100.0f) -> void;

auto UIColor(Label label, float* color, bool& dirty, Label id = "") -> void;

auto Theme() -> void;