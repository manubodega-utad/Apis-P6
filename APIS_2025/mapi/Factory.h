#pragma once
#include "Render.h"
#include "GL1Render.h"
#include "InputManager.h"
#include "GLFWInputManager.h"
#include <memory>

enum class GraphicsBackend {
    GL1 // OpenGL 1.0
};

enum class InputBackend {
    GLFW // GLFW
};

class Factory {
private:
    static GraphicsBackend selectedGraphicsBackend;
    static InputBackend selectedInputBackend;

public:
    // Getters y  para los backends
    static GraphicsBackend getSelectedGraphicsBackend();
    static InputBackend getSelectedInputBackend();

    // Setters
    static void setSelectedGraphicsBackend(GraphicsBackend backend);
    static void setSelectedInputBackend(InputBackend backend);

    // Métodos
    static Render* getNewRender(int width, int height);
    static InputManager* getNewInputManager(GLFWwindow* window);
    static bool isClosed(GLFWwindow* window);
};
