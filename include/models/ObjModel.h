#pragma once
#include "Model.h"
#include "ObjLoader.h" //Que será el nuevo lector

class ObjModel : public Model {
private:
    int numIndices;
    float m_angulo;

protected:
    void initGeometry() override;
    void init() override;

public: 
    float minY, maxY; // Para almacenar los valores mínimo y máximo de la altura    
    ObjModel(ShaderProgram* shader, const char* rutaArchivo);
    void renderModel(const glm::mat4& view, const glm::mat4& projection) override;
    void updateModel(float dt) override;
    void finish() override;
};