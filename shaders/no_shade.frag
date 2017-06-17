// From https://learnopengl.com/code_viewer.php?code=model_loading/model&type=fragment

#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform vec4 fragColor;

uniform sampler2D texture_diffuse1;

void main()
{
    color = vec4(texture(texture_diffuse1, TexCoords));
}
