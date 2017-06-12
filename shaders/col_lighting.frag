// Adapted from https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/2.2.basic_lighting_specular/2.2.basic_lighting.fs

#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform float ambientStrength;
uniform vec3 ambientLightColor;

uniform vec3 lamp1Pos;
uniform vec3 lamp2Pos;
uniform vec3 viewPos;
uniform vec3 lampLightColor;
uniform float lamp1LightStrength;
uniform float lamp2LightStrength;
uniform vec3 cameraLightColor;
uniform float cameraLightStrength;
uniform vec3 objectColor;

uniform float specularStrength;
uniform int shininess;


vec3 calc_dir_light(vec3 light_pos, float light_strength, vec3 light_color)
{
    // diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light_pos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light_strength * diff * light_color;

    // specular light
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * light_color;

    return (diffuse + specular);
}

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // ambient light
    vec3 ambient = ambientStrength * ambientLightColor;

    // lamp 1 light
    vec3 lamp1_dir_light = calc_dir_light(lamp1Pos, lamp1LightStrength, lampLightColor);

    // lamp 2 light
    vec3 lamp2_dir_light = calc_dir_light(lamp2Pos, lamp2LightStrength, lampLightColor);

    // camera-tracking light
    vec3 camera_dir_light = calc_dir_light(viewPos, cameraLightStrength, cameraLightColor);

    vec3 result = (ambient + lamp1_dir_light + lamp2_dir_light + camera_dir_light) * objectColor;
    FragColor = vec4(result, 1.0);
}
