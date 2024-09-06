#pragma once

static const char* _SHADER_scene_frag = R"(#version 410 core
#pragma debug(on)
#pragma optimize(off)

layout (location = 0) out vec4 frag_color;

void main() {
    frag_color = vec4(1.0, 1.0, 1.0, 1.0);
})";