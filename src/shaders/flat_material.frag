#version 320 es

#pragma debug(on)
#pragma optimize(off)

precision mediump float;

layout (location = 0) out vec4 outColor;

in vec2 textureCoords;

uniform sampler2D texture_0;

void main() {
    outColor = vec4(0.89, 0.47, 0.26, 1.0);
}