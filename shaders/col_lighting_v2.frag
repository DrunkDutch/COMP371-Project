// Adapted from https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/2.2.basic_lighting_specular/2.2.basic_lighting.fs

#version 330 core

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    bool enabled;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light1;
uniform Light light2;
uniform Light light3;


vec3 calc_dir_light(Light light, vec3 norm, vec3 viewDir)
{
    if (!light.enabled) {
        return vec3(0, 0, 0);
    } else {
        // ambient light
        vec3 ambient = vec3(0.439f,0.259f,0.078f) * texture(material.diffuse, TexCoords).rgb;

        // diffuse light
        vec3 lightDir = normalize(light.position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

        // specular light
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

        return (ambient + diffuse + specular);
    }
}

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // lamp 1 light
    vec3 lamp1_dir_light = calc_dir_light(light1, norm, viewDir);

    // lamp 2 light
    vec3 lamp2_dir_light = calc_dir_light(light2, norm, viewDir);

    // lamp 3 light
    vec3 lamp3_dir_light = calc_dir_light(light3, norm, viewDir);

    vec3 result = (lamp1_dir_light + lamp2_dir_light + lamp3_dir_light);
    FragColor = vec4(result, 1.0);
}
