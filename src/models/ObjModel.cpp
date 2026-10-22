#include "models/ObjModel.h"
#include <iostream>

//Llamamos al constructor de la clase base Model y le pasamos el shader
ObjModel::ObjModel(ShaderProgram* shader, const char* rutaArchivo)
    : Model(shader), numIndices(0)

{
    //Leer el archivo
    ObjLoader loader;
    if (!loader.cargarModelo(rutaArchivo)) {
        std::cerr << "Error en cargar OBJ: " << rutaArchivo << std::endl;
        return;
    }

    numIndices = loader.indices.size();

    //Agregadas
    this->minY = loader.minY;
    this->maxY = loader.maxY;

    // Generar y enlazar VAO, VBO y EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, loader.vertices.size() * sizeof(glm::vec3), &loader.vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, loader.indices.size() * sizeof(GLuint), &loader.indices[0], GL_STATIC_DRAW);

    //Ahora la posicion de los vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void ObjModel::renderModel(const glm::mat4& view, const glm::mat4& projection) {
    
    /*
    Todo este bloque fue lo que me dio la IA para que pudiera correr en mi distribución de 
    linux, antes de eso no podia visualizar el trabajo
    */
    //Activamos el shader
    m_shaderProgram->use(); 

    //Obtenemos el ID del shader
    GLint shaderID;
    glGetIntegerv(GL_CURRENT_PROGRAM, &shaderID);

    //Enviamos las matrices a la tarjeta gráfica
    GLuint modelLoc = glGetUniformLocation(shaderID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_model_mat));
    GLuint viewLoc = glGetUniformLocation(shaderID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    GLuint projLoc = glGetUniformLocation(shaderID, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Los limites de altura
    GLuint minLoc = glGetUniformLocation(shaderID, "minY");
    glUniform1f(minLoc, this->minY);

    GLuint maxLoc = glGetUniformLocation(shaderID, "maxY");
    glUniform1f(maxLoc, this->maxY);

    // Ahora solo se dibuja el modelo
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    //Hasta aquí
}

// Intento de implementacion de las rotaciones 
void ObjModel::updateModel(float dt) {
    //Esto para hacer rotaciones
       if (dt == 1)
    {
        m_angulo += dt *1.0;
        m_model_mat = glm::mat4(1.0f);
        m_model_mat= glm::rotate(m_model_mat,glm::radians(m_angulo),glm::vec3(1.0f,0.0f,0.0f));
    } else if (dt == 2)
    {
        m_model_mat=glm::rotate(m_model_mat,glm::radians(dt),glm::vec3(0.0f,1.0f,0.0f));
    } else if (dt == 3)
    {
        m_model_mat=glm::rotate(m_model_mat,glm::radians(dt),glm::vec3(0.0f,0.0f,1.0f));
    }
    
}

void ObjModel::initGeometry() {
    //Geometria inicializada en el constructor
}

void ObjModel::init() {
    //Inicializacion en el constructor
}

void ObjModel::finish() {
    //La clase Model ya lo hace, queda vacío 
}