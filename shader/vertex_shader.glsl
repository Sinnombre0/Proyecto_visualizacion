#version 400 core
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