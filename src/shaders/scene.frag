#version 320 es

#pragma debug(on)
#pragma optimize(off)

precision mediump float;

layout (location = 0) out vec4 frag_color;

void main() {
    frag_color = vec4(1.0, 1.0, 1.0, 1.0);
}