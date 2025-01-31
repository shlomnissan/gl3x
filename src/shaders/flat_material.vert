#version 410 core

#extension GL_ARB_shading_language_include : enable

#pragma inject_attributes

#pragma debug(on)
#pragma optimize(off)

#include "snippets/common_vert_params.glsl"

void main() {
    #include "snippets/common_vert_varyings.glsl"

    gl_Position = u_Projection * v_Position;
}