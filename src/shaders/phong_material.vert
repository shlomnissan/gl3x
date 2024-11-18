#version 320 es

#pragma inject_attributes

#pragma debug(on)
#pragma optimize(off)

in vec3 a_Position;
in vec3 a_Normal;
in vec2 a_TexCoord;

uniform mat3 u_NormalMatrix;
uniform mat4 u_ModelView;
uniform mat4 u_Projection;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_Position;

void main() {
    v_TexCoord = a_TexCoord;
    v_Normal = normalize(u_NormalMatrix * a_Normal);
    v_Position = (u_ModelView * vec4(a_Position, 1.0)).xyz;

    gl_Position = u_Projection * vec4(v_Position, 1.0);
}