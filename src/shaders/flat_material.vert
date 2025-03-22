#version 410 core

#extension GL_ARB_shading_language_include : enable

#pragma inject_attributes

#pragma debug(on)
#pragma optimize(off)

#include "snippets/vert_global_params.glsl"

void main() {
    #include "snippets/vert_main_varyings.glsl"

    gl_Position = u_Projection * v_Position;
}