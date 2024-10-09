#version 320 es

#pragma debug(on)
#pragma optimize(off)

#pragma inject_attributes

precision mediump float;

layout (location = 0) out vec4 FragColor;

uniform vec4 AttribColor;

void main() {
    FragColor = vec4(1.0);

    #ifdef USE_COLOR
        FragColor = FragColor * AttribColor;
    #endif
}