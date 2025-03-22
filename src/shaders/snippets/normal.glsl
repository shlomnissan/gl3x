#ifdef USE_FLAT_SHADED
    vec3 fdx = dFdx(v_Position.xyz);
	vec3 fdy = dFdy(v_Position.xyz);
	vec3 normal = normalize(cross(fdx, fdy));
#else
    vec3 normal = v_Normal;
    #ifdef USE_TWO_SIDED
        normal *= gl_FrontFacing ? 1.0 : -1.0;
    #endif
#endif