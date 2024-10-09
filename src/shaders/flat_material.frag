#version 320 es

#pragma debug(on)
#pragma optimize(off)

#pragma inject_attributes

precision mediump float;

layout (location = 0) out vec4 outColor;

void main() {
    outColor = vec4(0.89, 0.47, 0.26, 1.0);
}