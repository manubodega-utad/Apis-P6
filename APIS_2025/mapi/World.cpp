#include "World.h"

// Constructor
World::World() {}

// Getters
size_t World::getNumObjects() const {
    return objects.size();
}

Object* World::getObject(size_t index) const {
    if (index >= objects.size()) {
        throw std::out_of_range("Índice fuera de rango");
    }

    auto it = objects.begin();
    std::advance(it, index);
    return *it;
}

std::list<Object*>& World::getObjects() {
    return objects;
}

// Métodos
// Añadir un objeto
void World::addObject(Object* obj) {
    if (obj != nullptr) {
        objects.push_back(obj);
    }
}

// Eliminar un objeto
void World::removeObject(Object* obj) {
    objects.remove(obj);
}

// Actualiza el estado del mundo
void World::update(float deltaTime) {
    for (Object* obj : objects) {
        if (obj != nullptr) {
            obj->step(deltaTime);
        }
    }
}
