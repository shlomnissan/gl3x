#version 410 core

#extension GL_GOOGLE_include_directive : enable

#pragma inject_attributes

#include "snippets/vert_global_params.glsl"
#include "snippets/utilities.glsl"

void main() {
    #include "snippets/vert_main_varyings.glsl"

    vec4 position = model_view[3];
    vec2 scale = vec2(length(u_Model[0].xyz), length(u_Model[1].xyz));

    bool is_perspective = isPerspectiveMatrix(u_Projection);
    if (is_perspective) {
        scale *= -position.z;
    }

    position.xy += a_Position.xy * scale;

    gl_Position = u_Projection * position;
}