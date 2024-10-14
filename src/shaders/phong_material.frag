#include <version>

#pragma debug(on)
#pragma optimize(off)

#pragma inject_attributes

precision mediump float;

layout (location = 0) out vec4 FragColor;

in vec2 TexCoordinates;

uniform sampler2D AttribTextureMap;
uniform vec4 AttribColor;

void main() {
    FragColor = vec4(1.0);

    #ifdef USE_COLOR
        FragColor = FragColor * AttribColor;
    #endif

    #ifdef USE_TEXTURE_MAP
        FragColor = FragColor * texture(AttribTextureMap, TexCoordinates);
    #endif
}