#include "WindowGL.h"

void WindowGL::InitGLFW(){
    if (!glfwInit()) {
        std::cerr << "FAILED TO INITIALIZE GLFW\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "GLFW STARTED\n";

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    m_window = glfwCreateWindow(m_width, m_height, m_name, NULL, NULL );

    if(!m_window){
        std::cerr << "FAILED TO CREATE WINDOW\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // Antes de inicar el Glew (Solucionde la IA, antes no pidia ver el resultado)
    glfwMakeContextCurrent(m_window);
    std::cout<<"WINDOW CREATED\n";
}

void WindowGL::InitGLEW(){
    glewExperimental = GL_TRUE;
    
    GLenum err = glewInit();

    //Igualmente aqui, la IA me dio la solución para que "corriera"
    // En Linux con Wayland/Mesa, GLEW a veces arroja un falso error
    // pero sí logra cargar las funciones. Vamos a imprimirlo como advertencia y continuar.
    if (err != GLEW_OK) {
        std::cout << "Advertencia de GLEW (Ignorada): " << glewGetErrorString(err) << "\n";
    }
    
    // Limpiamos cualquier bandera de error residual de OpenGL
    glGetError();
    
    std::cout<<"GLEW STARTED\n";  
}