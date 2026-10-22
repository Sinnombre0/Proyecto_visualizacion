#ifndef EJES_H
#define EJES_H
#include <glm/glm.hpp>
#include "Model.h"

class Eje: public Model
{
private:
    GLfloat vertices[36];
public: 

    Eje(ShaderProgram* program, int) : Model(program){
        initGeometry();
        
        init();
        m_model_mat = glm::mat4(1.0f);
    }

    void initGeometry() override;

    void init() override;

    void renderModel(const glm::mat4& view, const glm::mat4& projection) override;

    void updateModel(float deltaTime) override;

    void updateModel(float deltaTime, int opcion) override;

    void finish() override;

}; 

#endif