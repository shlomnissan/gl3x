/*

This fragment shader snippet computes an adjusted normal vector
based on material properties and the interpolated vertex normal (v_Normal).
Directly using v_Normal in the fragment shader is not recommended.
Instead, use the generated normal variable for lighting calculations.

@var vec3 normal - Adjusted normal vector

*/

#ifdef USE_FLAT_SHADED
    vec3 fdx = dFdx(v_Position.xyz);
	vec3 fdy = dFdy(v_Position.xyz);
	vec3 normal = normalize(cross(fdx, fdy));
#else
    vec3 normal = normalize(v_Normal);

    #ifdef USE_NORMAL_MAPPING
        vec3 normal_tan = texture(u_NormalMap, v_TexCoord).rgb  * 2.0 - 1.0;
        normal = normalize(v_TBN * normal_tan);
    #endif

    #ifdef USE_TWO_SIDED
        normal *= gl_FrontFacing ? 1.0 : -1.0;
    #endif
#endif