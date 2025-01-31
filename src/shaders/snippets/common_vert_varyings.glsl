v_TexCoord = (u_TextureTransform * vec3(a_TexCoord, 1.0)).xy;
v_Normal = normalize(u_NormalMatrix * a_Normal);
v_ViewDir = normalize(-v_Position.xyz);
v_Position = u_ModelView * vec4(a_Position, 1.0);
v_FogDepth = -v_Position.z;