#version 320 es

#pragma debug(on)
#pragma optimize(off)

#pragma inject_attributes

precision mediump float;

in vec3 aPosition;
in vec3 aNormal;
in vec2 aTexCoordinates;

out vec2 TexCoordinates;

uniform mat4 Projection;
uniform mat4 ModelView;

void main() {
    TexCoordinates = aTexCoordinates;
    gl_Position = Projection * ModelView * vec4(aPosition, 1.0);
}