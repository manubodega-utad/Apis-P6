#pragma once
#include "Object3D.h" // Heredamos de Object3D para aprovechar su malla y material

class Billboard : public Object3D {
private:
    float spin; // Velocidad de rotación en el eje Z

public:
    // Constructor
    Billboard();

    // Getters
    float getSpin() const;

    // Setters
    void setSpin(float spin);

    //Métodos
    virtual void computeModelMatrix() override;
    virtual void step(float deltatime);
};

