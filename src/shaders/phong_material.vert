#version 320 es

#pragma inject_attributes

#pragma debug(on)
#pragma optimize(off)

in vec3 a_Position;
in vec3 a_Normal;
in vec2 a_TexCoord;

out vec2 v_TexCoord;
out vec3 v_Position;
out vec3 v_Normal;

uniform mat4 u_Projection;
uniform mat4 u_ModelView;

void getCameraSpace(out vec3 position, out vec3 normal) {
    // u_ModelView does not include non-uniform scaling so
    // we can use the upper-left 3x3 of the ModelView
    // matrix instead of the a normal matrix
    mat3 normal_matrix = mat3(
        u_ModelView[0].xyz,
        u_ModelView[1].xyz,
        u_ModelView[2].xyz
    );

    position = (u_ModelView * vec4(a_Position, 1.0)).xyz;
    normal = normalize(normal_matrix * a_Normal);
}

void main() {
    vec3 position;
    vec3 normal;
    getCameraSpace(position, normal);

    v_TexCoord = a_TexCoord;
    v_Position = position;
    v_Normal = normal;

    gl_Position = u_Projection * vec4(position, 1.0);
}