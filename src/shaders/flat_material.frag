#version 410 core

#extension GL_ARB_shading_language_include : enable

#pragma inject_attributes

#pragma debug(on)
#pragma optimize(off)

precision mediump float;

#include "snippets/frag_global_params.glsl"
#include "snippets/frag_global_fog.glsl"

void main() {
    vec3 output_color = u_Color;
    float opacity = u_Opacity;

    #ifdef USE_TEXTURE_MAP
        output_color *= texture(u_TextureMap, v_TexCoord).rgb;
        opacity *= texture(u_TextureMap, v_TexCoord).a;
    #endif

    #ifdef USE_FOG
        applyFog(output_color, v_FogDepth);
    #endif

    v_FragColor = vec4(output_color, opacity);
    v_FragColor = clamp(v_FragColor, 0.0, 1.0);
}