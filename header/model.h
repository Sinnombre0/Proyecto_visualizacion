#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../header/shader.h"

class Model{
public:

    Shader* shader;
    // 4 vertices
    // GLfloat vertices[20];
    // GLuint indices[6];

    // 6 vertices
    // GLfloat vertices[30];
    // GLuint indices[12];

    // 8 vertices
    GLfloat vertices[40];
    GLuint indices[18];

    float angle;
    glm::mat4 modelmat;
    GLuint VAO, VBO, EBO;

    Model();
    //Model(GLfloat* vertices, GLuint indices);

    void initModel();
    void renderModel(glm::mat4 view, glm::mat4 projection);
    void updateModel(float timeValue);
    void finish();


};