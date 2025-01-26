#pragma once
#include <vector>
#include <string>
#include "RenderProgram.h"

using namespace std;


class Material {
protected:
    RenderProgram* program;

public:
    // Constructor
    Material() : program(nullptr) {}

    // Destructor
    virtual ~Material() {
        if (program) {
            delete program;
            program = nullptr;
        }
    }

    // Getters
    RenderProgram* getProgram() const 
    {
        return program; 
    }

    // Métodos
    virtual void loadPrograms(vector<string>& files) = 0;
    virtual void prepare() = 0;
};
