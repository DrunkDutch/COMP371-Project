// From https://learnopengl.com/code_viewer.php?code=model_loading/model&type=fragment

#version 330 core

out vec4 color;

uniform vec4 fragColor;

void main()
{
    color = fragColor;
}
