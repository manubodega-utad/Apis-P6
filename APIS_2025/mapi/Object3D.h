#pragma once
#include "Object.h"

class Object3D : public Object {
public:
    // Constructor
    Object3D();

    // Destructor
    virtual ~Object3D();

    

    // Métodos
    void loadDataFromFile(const std::string& file) override;
    virtual void step(double deltaTime) = 0;
};