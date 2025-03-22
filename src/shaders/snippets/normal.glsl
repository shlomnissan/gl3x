#ifdef USE_FLAT_SHADED
    vec3 fdx = dFdx(v_Position.xyz);
	vec3 fdy = dFdy(v_Position.xyz);
	vec3 normal = normalize(cross(fdx, fdy));
#else
    #ifdef USE_TWO_SIDED
        float face_direction = gl_FrontFacing ? 1.0 : -1.0;
        vec3 normal = v_Normal * face_direction;
    #else
        vec3 normal = v_Normal;
    #endif
#endif