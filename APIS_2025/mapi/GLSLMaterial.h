#pragma once
#include "Material.h"
#include "GLSLProgram.h"

class GLSLMaterial : public Material {
public:
    GLSLMaterial();
    virtual ~GLSLMaterial() override;
    void loadPrograms(vector<string>& files) override;
    void prepare() override;
    void setColor(const glm::vec4& color) 
    { 
        this->color = color; 
    }

private:
    glm::vec4 color;
};
