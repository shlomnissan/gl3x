#version 410 core

#pragma inject_attributes

#pragma debug(on)
#pragma optimize(off)

precision highp float;

layout (location = 0) out vec4 v_FragColor;

struct DirectionalLight {
    vec3 Direction;
    vec4 Color;
};

struct PhongMaterial {
    vec3 DiffuseColor;
    vec3 SpecularColor;
    float Shininess;
};

in vec2 v_TexCoord;
in vec3 v_Position;
in vec3 v_Normal;

uniform vec4 u_AmbientLight;
uniform vec4 u_Diffuse;
uniform vec4 u_Specular;
uniform float u_Shininess;
uniform sampler2D u_TextureMap;

#if NUM_DIR_LIGHTS > 0
    uniform DirectionalLight u_DirectionalLights[NUM_DIR_LIGHTS];
#endif

vec3 phongShading(
    const in vec3 light_dir,
    const in vec3 light_color,
    const in PhongMaterial material
) {
    float diffuse_factor = max(dot(light_dir, v_Normal), 0.0);
    vec3 diffuse = light_color * material.DiffuseColor * diffuse_factor;
    vec3 specular = vec3(0.0);

    // If the diffuse factor is zero, the light is facing away from the surface
    // and no light contribution should be calculated, so we skip specular calculation.
    if (diffuse_factor > 0.0) {
        vec3 view_dir = normalize(-v_Position.xyz);
        vec3 halfway = normalize(light_dir + view_dir);
        specular = light_color * material.SpecularColor *
            pow(max(dot(halfway, v_Normal), 0.0), material.Shininess);
    }

    return diffuse + specular;
}

void main() {
    PhongMaterial material = PhongMaterial(
        u_Diffuse.rgb,
        u_Specular.rgb,
        u_Shininess
    );

    #ifdef USE_TEXTURE_MAP
        material.DiffuseColor *= texture(u_TextureMap, v_TexCoord).rgb;
    #endif

    v_FragColor = u_AmbientLight * vec4(material.DiffuseColor, 1.0);

    #if NUM_DIR_LIGHTS > 0
        for (int i = 0; i < NUM_DIR_LIGHTS; i++) {
            DirectionalLight light = u_DirectionalLights[i];
            v_FragColor += vec4(phongShading(light.Direction, light.Color.rgb, material), 1.0);
        }
    #endif
}