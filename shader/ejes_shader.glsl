#version 400 core

in vec3 ejesColor;
out vec4 Color;

void main()
{
    Color = vec4(ejesColor, 1.0);
}
