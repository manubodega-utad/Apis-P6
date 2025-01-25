#include "GL1Render.h"
#include <iostream>

// Constructor
GL1Render::GL1Render(int width, int height) : Render() {
    this->width = width;
    this->height = height;
    this->window = nullptr;
}

// Destructor
GL1Render::~GL1Render() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

// Getters
int GL1Render::getWidth() const {
    return width;
}

int GL1Render::getHeight() const {
    return height;
}

GLFWwindow* GL1Render::getWindow() const {
    return window;
}

//Setters
void GL1Render::setWidth(int newWidth) {
    width = newWidth;
}

void GL1Render::setHeight(int newHeight) {
    height = newHeight;
}

// Métodos
void GL1Render::init() {
    if (glfwInit() != GLFW_TRUE) {
        cout << "Error GLFWINIT " << __FILE__ << ":" << __LINE__ << endl;
    }
    else {
        // Crear ventana
        window = glfwCreateWindow(width, height, "APIS Demo1", NULL, NULL);
        if (!window) {
            cout << "Error WINDOW " << __FILE__ << ":" << __LINE__ << endl;
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);
        gladLoadGL(glfwGetProcAddress);

        // PARA LA PRÁCTICA 4
        //activar carácteristica de profundidad 
        //glEnable(GL_DEPTH_TEST);
    }
}

void GL1Render::setupObject(Object* obj)
{
    //PARA PRÁCTICA 4 VER CODIGO CLASE 25/01
    /*
    objList.push_back(obj);
    for (auto& mesh : obj->meshList) {
        if (boList.find(mesh->idObj) == boList.end())
        {
            BufferObject bo = { -1, -1, -1 };
            glGenVertexArrays(1, bo & .idArray);
            // .........
               
        }
    }*/
}

void GL1Render::removeObject(Object* obj)
{
}

//CAMBIAR PARA PRÁCTICA 4 VER CODIGO CLASE 25/01
// DIBUJAR PARA CADA UNA DE LAS MALLAS
// Dibuja una lista de objetos en pantalla
void GL1Render::drawObjects(const std::vector<Object*>* objs) {
    // Limpiar buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (auto& obj : *objs) {
        if (!obj->getMesh()) continue;

        auto mesh = obj->getMesh();
        auto vertices = mesh->getVertexList();

        glPushMatrix();
        {
            glm::mat4 model = obj->getModel();
            glMultMatrixf(glm::value_ptr(model));

            glBegin(GL_TRIANGLES);
            for (auto& vertex : *vertices) {
                glVertex3f(vertex.vPos.x, vertex.vPos.y, vertex.vPos.z);
            }
            glEnd();
        }
        glPopMatrix();
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool GL1Render::isClosed() const {
    return glfwWindowShouldClose(window);
}