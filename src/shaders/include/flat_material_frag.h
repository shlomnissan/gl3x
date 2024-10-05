#pragma once

static const char* _SHADER_flat_material_frag = R"(#version 320 es

#pragma debug(on)
#pragma optimize(off)

precision mediump float;

layout (location = 0) out vec4 outColor;

in vec2 textureCoords;

uniform sampler2D texture_0;

void main() {
    outColor = texture(texture_0, textureCoords);
})";