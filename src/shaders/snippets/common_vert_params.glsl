in vec3 a_Position;
in vec3 a_Normal;
in vec2 a_TexCoord;

uniform mat3 u_NormalMatrix;
uniform mat3 u_TextureTransform;
uniform mat4 u_ModelView;
uniform mat4 u_Projection;

out float v_FogDepth;
out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_ViewDir;
out vec4 v_Position;