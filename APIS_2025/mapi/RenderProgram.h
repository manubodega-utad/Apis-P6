#pragma once
#include <string>
#include <vector>
#include <map>
#include "common.h"
#include "Program.h"

using namespace std;

class RenderProgram {
protected:
    //Id del programa renderizado
    unsigned int idRenderProgram;
    vector<Program*> shaders;
    map<std::string, unsigned int> varList;

public:
    // Constructor
    RenderProgram() : idRenderProgram(0) {}

    // Destructor
    virtual ~RenderProgram() {}

    // Setters
    virtual void setInt(string& name, int val) = 0;
    virtual void setFloat(string& name, float val) = 0;
    virtual void setVec3(string& name, const glm::vec3& vec) = 0;
    virtual void setVec4(string& name, const glm::vec4& vec) = 0;
    virtual void setMatrix(string& name, const glm::mat4& mat) = 0;

    //Métodos
    virtual void addProgram(string& fileName) = 0;
    virtual void linkProgram() = 0;
    virtual void use() = 0;
    virtual void checkLinkerErrors() = 0;
};
