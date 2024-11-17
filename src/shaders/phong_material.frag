#version 320 es

#pragma inject_attributes

#pragma debug(on)
#pragma optimize(off)

precision mediump float;

layout (location = 0) out vec4 v_FragColor;

in vec2 v_TexCoord;

uniform sampler2D u_AttribTextureMap;
uniform vec4 u_AttribColor;

void main() {
    v_FragColor = vec4(1.0);

    #ifdef USE_COLOR
        v_FragColor *= u_AttribColor;
    #endif

    #ifdef USE_TEXTURE_MAP
        v_FragColor *= texture(u_AttribTextureMap, v_TexCoord);
    #endif
}