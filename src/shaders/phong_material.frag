#version 410 core

#extension GL_ARB_shading_language_include : enable

#pragma inject_attributes

#pragma debug(on)
#pragma optimize(off)

precision highp float;

#include "snippets/frag_global_params.glsl"
#include "snippets/frag_global_fog.glsl"

struct PhongMaterial {
    vec3 DiffuseColor;
    vec3 SpecularColor;
    float Shininess;
};

uniform PhongMaterial u_Material;
uniform vec3 u_AmbientLight;

vec3 phongShading(
    const in vec3 light_dir,
    const in vec3 light_color,
    const in vec3 normal
) {
    float diffuse_factor = max(dot(light_dir, normal), 0.0);
    vec3 diffuse = light_color * u_Material.DiffuseColor * diffuse_factor;

    // If the diffuse factor is zero, the light is facing away from the surface
    // and no light contribution should be calculated, so we skip specular calculation.
    vec3 specular = vec3(0.0);
    if (diffuse_factor > 0.0) {
        vec3 halfway = normalize(light_dir + v_ViewDir);
        specular = light_color * u_Material.SpecularColor *
            pow(max(dot(halfway, normal), 0.0), u_Material.Shininess);
    }

    return diffuse + specular;
}

#if NUM_LIGHTS > 0

struct Light {
    int Type; // 1 = directional, 2 = point, 3 = spot
    vec3 Color;
    vec3 Position;
    vec3 Direction;
    float ConeCos;
    float PenumbraCos;
    float Base;
    float Linear;
    float Quadratic;
};

uniform Light u_Lights[NUM_LIGHTS];

void processLights(inout vec3 color, const in vec3 normal) {
    for (int i = 0; i < NUM_LIGHTS; i++) {
        Light light = u_Lights[i];

        if (light.Type == 1 /* directional light */) {
            color += phongShading(light.Direction, light.Color, normal);
        }

        if (light.Type == 2 /* point light */) {
            vec3 light_dir = normalize(light.Position - v_Position.xyz);
            color += phongShading(light_dir, light.Color, normal);
        }

        if (light.Type == 3 /* spot light */) {
            vec3 light_dir = normalize(light.Position - v_Position.xyz);
            float angle_cos = dot(light_dir, light.Direction);
            if (angle_cos > light.ConeCos) {
                light.Color *= smoothstep(light.ConeCos, light.PenumbraCos, angle_cos);
                color += phongShading(light_dir, light.Color, normal);
            }
        }
    }
}

#endif

void main() {
    #include "snippets/frag_main_normal.glsl"

    vec3 output_color = u_AmbientLight;
    float opacity = u_Opacity;

    #ifdef USE_TEXTURE_MAP
        u_Material.DiffuseColor *= texture(u_TextureMap, v_TexCoord).rgb;
        opacity *= texture(u_TextureMap, v_TexCoord).a;
    #endif

    output_color *= u_Material.DiffuseColor;

    #if NUM_LIGHTS > 0
        processLights(output_color, normal);
    #endif

    #ifdef USE_FOG
        applyFog(output_color, v_ViewDepth);
    #endif

    v_FragColor = vec4(output_color, opacity);
    v_FragColor = clamp(v_FragColor, 0.0, 1.0);
}