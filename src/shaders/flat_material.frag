#version 410 core

#pragma inject_attributes

#pragma debug(on)
#pragma optimize(off)

precision mediump float;

layout (location = 0) out vec4 v_FragColor;

in float v_FogDepth;
in vec2 v_TexCoord;

uniform vec3 u_Color;
uniform float u_Opacity;
uniform sampler2D u_TextureMap;

#ifdef USE_FOG
    struct Fog {
        vec3 Color;
        float Near;
        float Far;
    };

    uniform Fog u_Fog;
#endif

void main() {
    v_FragColor = vec4(u_Color, 1.0);

    #ifdef USE_TEXTURE_MAP
        v_FragColor *= texture(u_TextureMap, v_TexCoord);
    #endif

    #ifdef USE_FOG
        float fog_factor = smoothstep(u_Fog.Near, u_Fog.Far, v_FogDepth);
        v_FragColor = mix(v_FragColor, vec4(u_Fog.Color, 1.0), fog_factor);
    #endif

    v_FragColor.a *= u_Opacity;
    v_FragColor = clamp(v_FragColor, 0.0, 1.0);
}