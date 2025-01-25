#pragma once

#include <list>
#include <stdexcept>
#include "Object.h"

class World {
private:
    std::list<Object*> objects;

public:
    // Constructor
    World();

    // Getters
    size_t getNumObjects() const;
    Object* getObject(size_t index) const;
    std::list<Object*>& getObjects();

    // Métodos
    void addObject(Object* obj);
    void removeObject(Object* obj);
    void update(float deltaTime);
};
