/* 
Comentado para no quitar lo que ya venia por si se ocupa

#version 410 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 fragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    fragColor = color;
    gl_Position = projection * view * model * vec4(position, 1.0);
}
*/

#version 330 core
layout (location = 0) in vec3 aPos;

// La altura
out float VertexHeight; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    // Altura del vértice
    VertexHeight = aPos.y; 
}