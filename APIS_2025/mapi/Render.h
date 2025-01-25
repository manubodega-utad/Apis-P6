#pragma once
#pragma once
#include <vector>
#include "Object.h"

class Render {
protected:
    int width;
    int height;

public:
    // Constructor y destructor
    Render() : width(800), height(600) {}
    virtual ~Render() = default;

    // Métodos virtuales puros
    

    // Getters
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

    // Setters
    virtual void setWidth(int newWidth) = 0;
    virtual void setHeight(int newHeight) = 0;

    //Metodos
    virtual void init() = 0;
    virtual void setupObject(Object* obj) = 0;
    virtual void removeObject(Object* obj) = 0;
    virtual void drawObjects(const std::vector<Object*>* objs) = 0;
    virtual bool isClosed() const = 0;
};