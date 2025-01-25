#include "Object.h"




// Constructor
Object::Object() : mesh(nullptr), tipo(ObjectType::Object1) {}

// Destructor
Object::~Object() {}

// Getters"
Mesh3D* Object::getMesh() const {
    return mesh;
}

void Object::setMesh(Mesh3D* newMesh) {
    mesh = newMesh;
}

// Setters"
int Object::getTipo() const {
    return static_cast<int>(tipo);
}

void Object::setTipo(int newTipo) {
    tipo = static_cast<ObjectType>(newTipo);
}