#version 410 core
in vec2 coordTex;
out vec4 FragColor;

void main()
{

        //Definimos el dominio utilizando coordenadas de textura 
        //
        //1. (0,0) x (1,1) a (-1,-1) x (1,1)
        float x = coordTex.x;
        float y = coordTex.y;
        float x1 = 2.0 * x - 1.0;
        float y1 = 2.0 * y - 1.0;
        
        vec3 col = vec3(1.0,0.0,0.0);
   
   FragColor = vec4(col, 1.0);
}