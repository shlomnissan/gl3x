/*

This vertex shader snippet calculates varyings that are passed to the fragment
shader. Refer to vert_global_params.glsl for the definitions of these varyings
and other global parameters shared between the vertex and fragment shaders.

*/

mat4 model_view = u_View * u_Model;
mat3 normal_matrix = transpose(inverse(mat3(model_view)));

v_TexCoord = (u_TextureTransform * vec3(a_TexCoord, 1.0)).xy;
v_Position = model_view * vec4(a_Position, 1.0);
v_Normal = normalize(normal_matrix * a_Normal);
v_ViewDir = normalize(-v_Position.xyz);
v_ViewDepth = -v_Position.z;