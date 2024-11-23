#version 320 es

#pragma inject_attributes

#pragma debug(on)
#pragma optimize(off)

precision mediump float;

layout (location = 0) out vec4 v_FragColor;

struct DirectionalLight {
    vec3 Direction;
    vec4 Color;
};

struct MaterialInfo {
    vec3 Kd;
    vec3 Ks;
    float Shininess;
};

in vec2 v_TexCoord;
in vec3 v_Position;
in vec3 v_Normal;

uniform sampler2D u_TextureMap;

uniform vec4 u_Color;
uniform vec4 u_AmbientLight;

uniform DirectionalLight u_DirectionalLights[NUM_DIR_LIGHTS];

vec3 phongModel(in DirectionalLight light, in MaterialInfo material, in vec3 position, in vec3 normal) {
    float direction_dot_normal = max(dot(light.Direction, normal), 0.0);

    vec3 diffuse = light.Color.rgb * material.Kd * direction_dot_normal;
    vec3 specular = vec3(0.0);

    // Without checking direction_dot_normal before computing the specular component,
    // specular highlights could appear on surfaces facing away from
    // the light, leading to unrealistic results. Some address this by
    // multiplying the specular component by the diffuse component, reducing
    // and altering its color. The solution here avoids this with an if statement.
    if (direction_dot_normal > 0.0) {
        vec3 v = normalize(-position.xyz);
        vec3 r = reflect(-light.Direction, normal);
        specular = light.Color.rgb * material.Ks *
            pow(max(dot(v, r), 0.0), material.Shininess);
    }

    return u_AmbientLight.rgb + diffuse + specular;
}

void main() {
    MaterialInfo material = MaterialInfo(
        vec3(u_Color),
        vec3(0.2, 0.2, 0.2),
        16.0
    );

    v_FragColor = vec4(phongModel(u_DirectionalLights[0], material, v_Position, v_Normal), 1.0);

    #ifdef USE_TEXTURE_MAP
        v_FragColor *= texture(u_TextureMap, v_TexCoord);
    #endif
}