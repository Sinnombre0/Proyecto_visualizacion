#include "models/Ejes.h"

void Eje::initGeometry(){
    const GLfloat ejesVertices[] = {
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 2.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 1.0f
    };
    for (int i = 0; i < 36; ++i) {
        vertices[i] = ejesVertices[i];
    }
}

void Eje::init(){
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}


void Eje::renderModel(const glm::mat4& view, const glm::mat4& projection){
    m_shaderProgram->use();

    m_shaderProgram->setMat4x4("model", m_model_mat);
    m_shaderProgram->setMat4x4("view", view);
    m_shaderProgram->setMat4x4("projection", projection);

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 6);
    glBindVertexArray(0);
}

void Eje::updateModel(float){
}

void Eje::finish(){
}