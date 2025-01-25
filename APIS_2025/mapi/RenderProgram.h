#pragma once
#include <string>
#include <vector>
#include <map>

#include "common.h"
#include "Program.h"

using namespace std;

class RenderProgram {
protected:
    vector<Program*> shaders;
    unsigned int idRenderProgram;
    map<std::string, unsigned int> varList;

public:
    // Constructor
    RenderProgram() : idRenderProgram(0) {}

    // Destructor
    virtual ~RenderProgram() {}
    virtual void addProgram(const std::string& fileName) = 0;
    virtual void linkProgram() = 0;
    virtual void use() = 0;
    virtual void checkLinkerErrors() = 0;

    // Setters
    virtual void setInt(const std::string& name, int val) = 0;
    virtual void setFloat(const std::string& name, float val) = 0;
    virtual void setVec3(const std::string& name, const glm::vec3& vec) = 0;
    virtual void setVec4(const std::string& name, const glm::vec4& vec) = 0;
    virtual void setMatrix(const std::string& name, const glm::mat4& mat) = 0;
};
