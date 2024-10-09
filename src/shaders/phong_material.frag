#version 320 es

#pragma debug(on)
#pragma optimize(off)

#pragma inject_attributes

precision mediump float;

layout (location = 0) out vec4 outColor;

void main() {
    outColor = vec4(0.51, 0.73, 0.66, 1.0);
}