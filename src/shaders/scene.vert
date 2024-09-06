#version 410 core
#pragma debug(on)
#pragma optimize(off)

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aTextureCords;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main() {
    gl_Position = Projection * View * Model * vec4(aPosition, 1.0);
}