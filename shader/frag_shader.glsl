#version 400 core
in float VertexHeight;

// Usamos los límites que había puesto
uniform float minY;
uniform float maxY;

out vec4 FragColor;

void main() {
    // Altura de 0.0 a 1.0
    float t = (VertexHeight - minY) / (maxY - minY);
    
    vec3 colorAzul = vec3(0.0, 0.0, 1.0);
    vec3 colorAmarillo = vec3(1.0, 1.0, 0.0);
    vec3 colorRojo = vec3(1.0, 0.0, 0.0);
    
    vec3 colorFinal;
    if (t < 0.5) {
        // Mitad inferior: de azul a amarillo
        colorFinal = mix(colorAzul, colorAmarillo, t * 2.0);
    } else {
        // Mitad superior: de amarillo a rojo
        colorFinal = mix(colorAmarillo, colorRojo, (t - 0.5) * 2.0);
    }
    
    FragColor = vec4(colorFinal, 1.0);
}