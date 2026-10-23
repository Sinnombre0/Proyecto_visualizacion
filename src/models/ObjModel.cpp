#include "models/ObjModel.h"
#include <iostream>
#include <algorithm>

//Llamamos al constructor de la clase base Model y le pasamos el shader
ObjModel::ObjModel(ShaderProgram* shader, const char* rutaArchivo): Model(shader), numIndices(0) {
    //Leer el archivo
    ObjLoader loader;
    if (!loader.cargarModelo(rutaArchivo)) {
        std::cerr << "Error en cargar OBJ: " << rutaArchivo << std::endl;
        return;
    }

    //Tenemos que calcular el centro, para esto se crearon el min y max de X, Y y Z 
    //Solo sumando y dividiendo obtenemos el centro
    glm::vec3 centro (
        (loader.minX + loader.maxX) / 2.0f,
        (loader.minY + loader.maxY) / 2.0f,
        (loader.minZ + loader.maxZ) / 2.0f
    );

    //Ahora tenemos que saber cuanto mide solamente restando el minimo al maximo de cada uno
    glm::vec3 longitud (
        loader.maxX - loader.minX,
        loader.maxY - loader.minY,
        loader.maxZ - loader.minZ
    );


    //Tomamos el mas grande y lo convertimos en el actor de escala
    float maxGrande = std::max({longitud.x, longitud.y, longitud.z});
    float scalaFactor = 2.0f / maxGrande;
    

    // Hacemos la matriz
    //glm::mat4 modeloMatriz = glm::mat4(1.0f);

    //Primero hacemos que nuestro objeto se mueva alcentro y despues se escale
    m_model_mat = glm::mat4(1.0f);
    m_model_mat = glm::scale(m_model_mat, glm::vec3(scalaFactor));
    m_model_mat = glm::translate(m_model_mat, -centro); //negativo paa estar en (0,0,0)

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

void ObjModel::renderModel(const glm::mat4& view, const glm::mat4& projection, float escalaUI) {
    
    //Activamos el shader
    m_shaderProgram->use(); 

    //Obtenemos el ID del shader
    GLint shaderID;
    glGetIntegerv(GL_CURRENT_PROGRAM, &shaderID);

    //Escalamiento
    glm::mat4 matrizFinal = glm::scale(m_model_mat, glm::vec3(escalaUI));

    //Enviamos las matrices a la tarjeta gráfica
    GLuint modelLoc = glGetUniformLocation(shaderID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrizFinal));
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
}

void ObjModel::updateModel(float dt) {    
}

// Intento de implementacion de las rotaciones en los ejes x, y, z
void ObjModel::updateModel(float dt, int opcion){
    glm::vec3 eje;

    if (opcion == 1) {
        eje = glm::vec3(1.0f, 0.0f, 0.0f);
    } else if (opcion == 2) {
        eje = glm::vec3(0.0f, 1.0f, 0.0f);
    } else if (opcion == 3) {
        eje = glm::vec3(0.0f, 0.0f, 1.0f);
    } else {
        return;
    }

    m_model_mat = glm::rotate(m_model_mat, glm::radians(dt), eje );
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