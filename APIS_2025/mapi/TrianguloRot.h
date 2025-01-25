#pragma once

#include "Object3D.h"
#include "System.h"
#include "Mesh3D.h"
#include <iostream>
#include <cmath>

class TrianguloRot : public Object3D {
public:
    // Constructor
    TrianguloRot();

    // Destructor
    ~TrianguloRot() override;

    // Metodos
    void step(double deltaTime) override;
    void loadDataFromFile(const std::string& file) override;
};
