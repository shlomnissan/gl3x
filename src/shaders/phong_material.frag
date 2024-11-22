#version 320 es

#pragma inject_attributes

#pragma debug(on)
#pragma optimize(off)

precision mediump float;

layout (location = 0) out vec4 v_FragColor;

struct LightInfo {
    vec4 Position;
    vec3 L;  // Diffuse/Specular
};

struct MaterialInfo {
    vec3 Kd; // Diffuse
    vec3 Ks; // Specular
    float Shininess;
};

in vec2 v_TexCoord;
in vec3 v_Position;
in vec3 v_Normal;

uniform sampler2D u_TextureMap;
uniform vec4 u_Color;
uniform vec4 u_AmbientLight;

vec3 phongModel(in LightInfo light, in MaterialInfo material, in vec3 position, in vec3 normal) {
    vec3 s = normalize(vec3(light.Position) - position);
    float s_dot_n = max(dot(s, normal), 0.0);

    vec3 diffuse = light.L * material.Kd * s_dot_n;
    vec3 specular = vec3(0.0);

    // Without checking s_dot_n before computing the specular component,
    // specular highlights could appear on surfaces facing away from
    // the light, leading to unrealistic results. Some address this by
    // multiplying the specular component by the diffuse component, reducing
    // and altering its color. The solution here avoids this with an if statement.
    if (s_dot_n > 0.0) {
        vec3 v = normalize(-position.xyz);
        vec3 r = reflect(-s, normal);
        specular = light.L * material.Ks *
            pow(max(dot(v, r), 0.0), material.Shininess);
    }

    return u_AmbientLight.rgb + diffuse + specular;
}

void main() {
    LightInfo light = LightInfo(
        vec4(2.0, 2.0, 2.0, 1.0),
        vec3(1.0, 1.0, 1.0)
    );

    MaterialInfo material = MaterialInfo(
        vec3(u_Color),
        vec3(0.2, 0.2, 0.2),
        16.0
    );

    v_FragColor = vec4(phongModel(light, material, v_Position, v_Normal), 1.0);

    #ifdef USE_TEXTURE_MAP
        v_FragColor *= texture(u_TextureMap, v_TexCoord);
    #endif
}