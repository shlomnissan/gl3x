/*

This fragment shader snippet applies a fog effect based on the fragment's
distance from the camera. It supports two fog types: linear and exponential,
but only one can be active at a time. To use the fog effect, call the
applyFog function with the color and depth as arguments.

@func void applyFog(inout vec4 color, float depth)
    @desc Applies the fog effect to the color based on the depth
    @param inout vec4 color - The color to be modified by the fog effect
    @param const in float depth - The depth of the fragment in view space
    @return void

*/

#ifdef USE_LINEAR_FOG

struct Fog {
    vec3 Color;
    float Near;
    float Far;
};
uniform Fog u_LinearFog;

void applyFog(inout vec4 color, const in float depth) {
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

void applyFog(inout vec4 color, const in float depth) {
    float fog_factor = 1.0 - exp(-u_ExponentialFog.Density * u_ExponentialFog.Density * depth * depth);
    color = mix(color, vec4(u_ExponentialFog.Color, 1.0), fog_factor);
}

#endif