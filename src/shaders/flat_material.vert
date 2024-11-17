#version 320 es

#pragma inject_attributes

#pragma debug(on)
#pragma optimize(off)

in vec3 a_Position;
in vec3 a_Normal;
in vec2 a_TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_Projection;
uniform mat4 u_ModelView;

void main() {
    v_TexCoord = a_TexCoord;
    gl_Position = u_Projection * u_ModelView * vec4(a_Position, 1.0);
}