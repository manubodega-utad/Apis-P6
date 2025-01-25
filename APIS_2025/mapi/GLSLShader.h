#pragma once
#include "Program.h"

using namespace std;

class GLSLShader : public Program {
private:
    std::string code;
public:
    GLSLShader(const std::string& fileName);
    ~GLSLShader() override;

    void readFile() override;
    void compile() override;
    void checkErrors() override;
};
