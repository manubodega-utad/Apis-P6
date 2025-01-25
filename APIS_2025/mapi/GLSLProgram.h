#pragma once
#include "RenderProgram.h"
#include <iostream>

using namespace std;

class GLSLProgram : public RenderProgram {
public:
    // Constructor
    GLSLProgram();

    // Destructor
    ~GLSLProgram() override;

    // Setters
    void setInt(string& name, int val) override;
    void setFloat(string& name, float val) override;
    void setVec3(string& name, const glm::vec3& vec) override;
    void setVec4(string& name, const glm::vec4& vec) override;
    void setMatrix(string& name, const glm::mat4& mat) override;

    // Métodos
    void addProgram(string& fileName) override;
    void linkProgram() override;
    void use() override;
    void checkLinkerErrors() override;

private:
    // Métodos propios
    void readVarList();
    unsigned int getVarLocation(std::string varName);
};
