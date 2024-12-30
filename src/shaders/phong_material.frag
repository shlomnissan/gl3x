#version 410 core

#pragma inject_attributes

#pragma debug(on)
#pragma optimize(off)

precision highp float;

layout (location = 0) out vec4 v_FragColor;

struct PhongMaterial {
    vec3 DiffuseColor;
    vec3 SpecularColor;
    float Shininess;
};

in float v_FogDepth;
in vec2 v_TexCoord;
in vec3 v_Normal;
in vec4 v_Position;

uniform vec3 u_AmbientLight;
uniform vec3 u_Diffuse;
uniform vec3 u_Specular;
uniform float u_Shininess;
uniform sampler2D u_TextureMap;

#ifdef USE_FOG
    struct Fog {
        vec3 Color;
        float Near;
        float Far;
    };

    uniform Fog u_Fog;
#endif

#if NUM_DIR_LIGHTS > 0
    struct DirectionalLight {
        vec3 Direction;
        vec3 Color;
    };

    uniform DirectionalLight u_DirectionalLights[NUM_DIR_LIGHTS];
#endif

#if NUM_POINT_LIGHTS > 0
    struct PointLight {
        vec4 Position;
        vec3 Color;
        float Distance;
        float Decay;
    };

    uniform PointLight u_PointLights[NUM_POINT_LIGHTS];
#endif

#if NUM_SPOT_LIGHTS > 0
    struct SpotLight {
        vec4 Position;
        vec3 Color;
        vec3 Direction;
        float Distance;
        float Decay;
        float ConeCos;
        float PenumbraCos;
    };

    uniform SpotLight u_SpotLights[NUM_SPOT_LIGHTS];
#endif

float distanceAttenuation(const in float light_distance, const in float cutoff_distance, const in float decay_exponent) {
	if( cutoff_distance > 0.0 && decay_exponent > 0.0 ) {
		return pow(clamp(-light_distance / cutoff_distance + 1.0, 0.0, 1.0), decay_exponent);
	}
	return 1.0;
}

vec3 phongShading(const in vec3 light_dir, const in vec3 light_color, const in PhongMaterial material) {
    vec3 normal = normalize(v_Normal);
    float diffuse_factor = max(dot(light_dir, normal), 0.0);
    vec3 diffuse = light_color * material.DiffuseColor * diffuse_factor;
    vec3 specular = vec3(0.0);

    // If the diffuse factor is zero, the light is facing away from the surface
    // and no light contribution should be calculated, so we skip specular calculation.
    if (diffuse_factor > 0.0) {
        vec3 view_dir = normalize(-v_Position.xyz);
        vec3 halfway = normalize(light_dir + view_dir);
        specular = light_color * material.SpecularColor *
            pow(max(dot(halfway, normal), 0.0), material.Shininess);
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

    v_FragColor = vec4(u_AmbientLight * material.DiffuseColor, 1.0f);

    #if NUM_DIR_LIGHTS > 0
        for (int i = 0; i < NUM_DIR_LIGHTS; i++) {
            DirectionalLight light = u_DirectionalLights[i];
            v_FragColor += vec4(phongShading(light.Direction, light.Color.rgb, material), 1.0);
        }
    #endif

    #if NUM_POINT_LIGHTS > 0
        for (int i = 0; i < NUM_POINT_LIGHTS; i++) {
            PointLight light = u_PointLights[i];
            vec3 v = light.Position.xyz - v_Position.xyz;
            vec3 direction = normalize(v);
            float light_distance = length(v);
            light.Color *= distanceAttenuation(light_distance, light.Distance, light.Decay);
            v_FragColor += vec4(phongShading(direction, light.Color.rgb, material), 1.0);
        }
    #endif

    #if NUM_SPOT_LIGHTS > 0
        for (int i = 0; i < NUM_SPOT_LIGHTS; i++) {
            SpotLight light = u_SpotLights[i];
            vec3 v = light.Position.xyz - v_Position.xyz;
            vec3 direction = normalize(v);
            float light_distance = length(v);
            float angle_cos = dot(direction, light.Direction);
            if (angle_cos > light.ConeCos) {
                light.Color *= smoothstep(light.ConeCos, light.PenumbraCos, angle_cos);
                light.Color *= distanceAttenuation(light_distance, light.Distance, light.Decay);
                v_FragColor += vec4(phongShading(direction, light.Color.rgb, material), 1.0);
            } else {
                light.Color = vec3(0.0);
            }
        }
    #endif

    #ifdef USE_FOG
        float fog_factor = smoothstep(u_Fog.Near, u_Fog.Far, v_FogDepth);
        v_FragColor = mix(v_FragColor, vec4(u_Fog.Color, 1.0), fog_factor);
    #endif

    v_FragColor = clamp(v_FragColor, 0.0, 1.0);
}