#pragma once

static const char* _SHADER_phong_material_frag = R"(#version 320 es

#pragma debug(on)
#pragma optimize(off)

precision mediump float;

layout (location = 0) out vec4 outColor;

in vec2 textureCoords;

uniform sampler2D texture_0;

void main() {
    outColor = vec4(0.51, 0.73, 0.66, 1.0);
})";