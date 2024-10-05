#pragma once

static const char* _SHADER_flat_material_vert = R"(#version 320 es

#pragma debug(on)
#pragma optimize(off)

precision mediump float;

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextureCoords;

out vec2 textureCoords;

uniform mat4 Projection;
uniform mat4 ModelView;

void main() {
    textureCoords = aTextureCoords;
    gl_Position = Projection * ModelView * vec4(aPosition, 1.0);
})";