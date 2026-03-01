#include "System.h"
#include <iostream>

// Inicialización
Render* System::render = nullptr;
InputManager* System::inputManager = nullptr;
bool System::end = false;
World* System::world = nullptr;
glm::mat4 System::ModelMatrix = glm::mat4(1.0f);

// Getters
World* System::getWorld() {
    return world;
}

const glm::mat4& System::getModelMatrix() {
    return ModelMatrix;
}

// Setters
void System::setWorld(World* newWorld) {
    if (world) {
        delete world;
    }
    world = newWorld;
}

void System::setModelMatrix(const glm::mat4& modelMatrix) {
    ModelMatrix = modelMatrix;
}

// Métodos
void System::initSystem() {
    // Seleccionar los backends
    Factory::setSelectedGraphicsBackend(GraphicsBackend::GL4);
    Factory::setSelectedInputBackend(InputBackend::GLFW);

    // Inicializar Render
    render = Factory::getNewRender(1600, 1200);
    render->init();

    // Validación para obtener ventana
    GLFWwindow* window = nullptr;
    if (auto* glRender = dynamic_cast<GL1Render*>(render)) {
        window = glRender->getWindow();
    }

    // Inicializar inputManager
    inputManager = Factory::getNewInputManager(window);
    inputManager->init();

    // Inicializar mundo
    world = new World();
}

// Añade un objeto al mundo
void System::addObject(Object* obj) {
    if (world) {
        world->addObject(obj);

        if (render) {
            render->setupObject(obj);
        }
    }
}

// Termina la ejecución del sistema
void System::exit() {
    end = true;
}

// Bucle principal del sistema
void System::mainLoop() {
    if (!render || !inputManager || !world) {
        std::cerr << "Error: El sistema no está completamente inicializado." << std::endl;
        return;
    }

    // Obtener ventana
    auto* glRender = dynamic_cast<GL1Render*>(render);
    GLFWwindow* window = glRender->getWindow();

    // Preparar los objetos para el renderizado
    for (Object* obj : world->getObjects()) {
        render->setupObject(obj);
    }

    // Bucle principal
    float newTime = static_cast<float>(glfwGetTime());
    float deltaTime = 0;
    float lastTime = newTime;

    while (!end) {
        // Calcular deltaTime
        newTime = static_cast<float>(glfwGetTime());
        deltaTime = newTime - lastTime;
        lastTime = newTime;

        // Actualizar el mundo
        world->update(deltaTime);

        // Limpiar buffers
        render->clearBuffers();

		// Ordenar Objetos por Distancia a la Cámara
        std::map<float, Object*> orderedMap;
        std::vector<Object*> opaqueObjects;
        std::vector<Object*> transparentObjects;

        Camera* cam = world->getActiveCamera();
        glm::vec3 camPos = cam ? cam->getPosition() : glm::vec3(0.0f);

        for (auto& obj : world->getObjects()) {
            if (!obj || obj->getMeshes().empty()) continue;

            float alpha = obj->getMeshes()[0]->getMaterial()->getColorRGBA().a;
            BlendMode blend = obj->getMeshes()[0]->getMaterial()->getBlendMode();

            if (alpha < 1.0f || blend != BlendMode::NONE) {
                glm::vec3 objPos = glm::vec3(obj->getModel()[3]);
                float distance = glm::distance(camPos, objPos);
                orderedMap[distance] = obj;
            }
            else {
                opaqueObjects.push_back(obj);
            }
        }

        for (auto obj = orderedMap.rbegin(); obj != orderedMap.rend(); ++obj) {
            transparentObjects.push_back(obj->second);
        }
        

        // Dibujar los objetos
        render->drawObjects(&opaqueObjects);
        render->drawObjects(&transparentObjects);

        // Intercambiar buffers
        render->swapBuffers();

        // Cierre de Ventana
        if (Factory::isClosed(window)) {
            exit();
        }
    }

    // Limpiar recursos
    delete render;

}
