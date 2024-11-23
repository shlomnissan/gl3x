#version 320 es

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

uniform vec4 u_Diffuse;
uniform vec4 u_Specular;
uniform float u_Shininess;
uniform sampler2D u_TextureMap;

uniform vec4 u_AmbientLight;
uniform DirectionalLight u_DirectionalLights[NUM_DIR_LIGHTS];

vec3 phongDirectional(const in int light_index, in PhongMaterial material, in vec3 position, in vec3 normal) {
    DirectionalLight light = u_DirectionalLights[light_index];

    float dot_dir_normal = max(dot(light.Direction, normal), 0.0);

    vec3 diffuse = light.Color.rgb * material.DiffuseColor * dot_dir_normal;
    vec3 specular = vec3(0.0);

    if (dot_dir_normal > 0.0) {
        vec3 v = normalize(-position.xyz);
        vec3 r = reflect(-light.Direction, normal);
        specular = light.Color.rgb * material.SpecularColor *
            pow(max(dot(v, r), 0.0), material.Shininess);
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
        material.DiffuseColor = u_Diffuse.rgb * texture(u_TextureMap, v_TexCoord);
    #endif

    v_FragColor = u_AmbientLight;
    for (int i = 0; i < NUM_DIR_LIGHTS; i++) {
        v_FragColor += vec4(phongDirectional(i, material, v_Position, v_Normal), 1.0);
    }
}