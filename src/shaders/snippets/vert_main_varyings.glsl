/*

This vertex shader snippet calculates varyings that are passed to the fragment
shader. Refer to vert_global_params.glsl for the definitions of these varyings
and other global parameters shared between the vertex and fragment shaders.

*/

mat4 model_view = u_View * u_Model;

#ifdef USE_INSTANCING
    model_view *= a_InstanceTransform;
    v_InstanceColor = a_InstanceColor;
#endif

#ifdef USE_VERTEX_COLOR
    v_Color = a_Color;
#endif

mat3 normal_matrix = transpose(inverse(mat3(model_view)));

v_Position = model_view * vec4(a_Position, 1.0);
v_TexCoord = (u_TextureTransform * vec3(a_TexCoord, 1.0)).xy;
v_Normal = normalize(normal_matrix * a_Normal);
v_ViewDir = normalize(-v_Position.xyz);
v_ViewDepth = -v_Position.z;

#ifdef USE_NORMAL_MAPPING
    vec3 tangent = normalize(mat3(model_view) * a_Tangent.xyz);
    vec3 bitangent = normalize(cross(v_Normal, tangent)) * a_Tangent.w;
    v_TBN = mat3(tangent, bitangent, v_Normal);
#endif