layout (location = 0) out vec4 v_FragColor;

in float v_FogDepth;
in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_ViewDir;
in vec4 v_Position;

uniform vec3 u_Color;
uniform float u_Opacity;
uniform sampler2D u_TextureMap;