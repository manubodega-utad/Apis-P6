#include "GLSLMaterial.h"

GLSLMaterial::GLSLMaterial()
    : Material(),
    color(1.0f, 1.0f, 1.0f, 1.0f)
{
    this->program = new GLSLProgram();
}

GLSLMaterial::~GLSLMaterial() {}

void GLSLMaterial::loadPrograms(vector<string>& files) {
    for (auto& file : files) {
        program->addProgram(file);
    }

    program->linkProgram();
}

void GLSLMaterial::prepare() {
    program->use();
    auto* glsl = dynamic_cast<GLSLProgram*>(program);
    if (glsl) {
        string uColor = "uColor";
        glsl->setVec4(uColor, color);

        /*
        // Setear matrices de transformación
        glsl->setMatrix("model", modelMatrix);
        glsl->setMatrix("view", viewMatrix);
        glsl->setMatrix("projection", projectionMatrix);

        // Setear texturas (asumiendo que tienes texturas)
        glsl->setInt("uTexture1", 0); // Textura en la unidad 0
        glsl->setInt("uTexture2", 1); // Textura en la unidad 1

        // Setear parámetros de iluminación
        glsl->setVec3("uLightPosition", lightPosition);
        glsl->setFloat("uShininess", shininess);
        */

    }else 
    {
        cout << "[GLSLMaterial] ERROR: No se pudo hacer dynamic_cast a GLSLProgram" << endl;
    }
}
