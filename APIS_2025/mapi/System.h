#pragma once
#include "Render.h"
#include "InputManager.h"
#include "Factory.h"
#include "World.h"
#include <chrono>

class System {
protected:
    
    
    static bool end;
    static World* world;

public:
    static Render* render;
    static InputManager* inputManager;
    // Getters
    static World* getWorld();

    // Setters
    static void setWorld(World* newWorld);

    // Métodos estáticos
    static void initSystem();
    static void addObject(Object* obj);
    static void exit();
    static void mainLoop();
};
