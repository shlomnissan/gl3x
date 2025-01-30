#ifdef USE_LINEAR_FOG
struct Fog {
    vec3 Color;
    float Near;
    float Far;
};
uniform Fog u_LinearFog;

void applyFog(inout vec4 color, float depth) {
    float fog_factor = smoothstep(u_LinearFog.Near, u_LinearFog.Far, depth);
    color = mix(color, vec4(u_LinearFog.Color, 1.0), fog_factor);
}
#endif

#ifdef USE_EXPONENTIAL_FOG
struct Fog {
    vec3 Color;
    float Density;
};
uniform Fog u_ExponentialFog;

void applyFog(inout vec4 color, float depth) {
    float fog_factor = 1.0 - exp(-u_ExponentialFog.Density * u_ExponentialFog.Density * depth * depth);
    color = mix(color, vec4(u_ExponentialFog.Color, 1.0), fog_factor);
}
#endif