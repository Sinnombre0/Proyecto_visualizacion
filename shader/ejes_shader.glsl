#version 400 core

in vec3 ejesColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(ejesColor, 1.0);
}
