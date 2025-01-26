#include "GLSLProgram.h"
#include "GLSLShader.h"

using namespace std;
GLSLProgram::GLSLProgram() {
    idRenderProgram = 0;
}

GLSLProgram::~GLSLProgram() {
    // Liberar los shaders
    for (auto* sh : shaders) {
        delete sh;
    }
}

void GLSLProgram::addProgram(string& fileName) {
    //useProgram ??
    GLSLShader* shader = new GLSLShader(fileName);
    shader->readFile();
    shader->compile();
    shader->checkErrors();

    // Lo guardamos
    shaders.push_back(shader);
}

void GLSLProgram::linkProgram() {
    // Crear un programa
    idRenderProgram = glCreateProgram();

    for (auto* sh : shaders) {
        glAttachShader(idRenderProgram, sh->getID());
    }
    // Linkar
    glLinkProgram(idRenderProgram);

    // Comprobar errores de link
    checkLinkerErrors();
    readVarList();
}

void GLSLProgram::use() {
    glUseProgram(idRenderProgram);
}

void GLSLProgram::checkLinkerErrors() {
    GLint linked;
    glGetProgramiv(idRenderProgram, GL_LINK_STATUS, &linked);
    if (linked != GL_TRUE) {
        GLsizei log_length = 0;
        char message[1024];
        glGetProgramInfoLog(idRenderProgram, 1024, &log_length, message);
        std::cout << "ERROR \n" << message << "\n\n";
    }
    else {
        std::cout << "[GLSLProgram] Programa linkado correctamente\n";
    }
}

void GLSLProgram::readVarList() {
    int numAttributes = 0;
    int numUniforms = 0;
    glGetProgramiv(idRenderProgram, GL_ACTIVE_ATTRIBUTES, &numAttributes);
    for (int i = 0; i < numAttributes; i++)
    {
        char varName[100];
        int bufSize = 100, length = 0, size = 0;
        GLenum type = -1;
        glGetActiveAttrib(idRenderProgram, (GLuint)i, bufSize, &length, &size, &type, varName);
        varList[std::string(varName)] = glGetAttribLocation(idRenderProgram, varName);
    }
    glGetProgramiv(idRenderProgram, GL_ACTIVE_UNIFORMS, &numUniforms);
    for (int i = 0; i < numUniforms; i++)
    {
        char varName[100];
        int bufSize = 100, length = 0, size = 0;
        GLenum type = -1;
        glGetActiveUniform(idRenderProgram, (GLuint)i, bufSize, &length, &size, &type, varName);
        varList[std::string(varName)] = glGetUniformLocation(idRenderProgram, varName);
    }
}


unsigned int GLSLProgram::getVarLocation(std::string varName) {
    if (varList.find(varName) != varList.end())
        return varList[varName];
    else {
        std::cout << "ERROR: variable " << varName << " no encontrada en shader\n";
        return -1;
    }
}


// SETTERS
void GLSLProgram::setInt(string& name, int val) {
    auto location = getVarLocation(name);
    if (location != (unsigned int)-1) {
        glUniform1i(location, val);
    }
}

void GLSLProgram::setFloat(std::string& name, float val) {
    auto location = getVarLocation(name);
    if (location != (unsigned int)-1) {
        glUniform1f(location, val);
    }
}

void GLSLProgram::setVec3(std::string& name, const glm::vec3& vec) {
    auto location = getVarLocation(name);
    if (location != (unsigned int)-1) {
        glUniform3f(location, vec.x, vec.y, vec.z);
    }
}

void GLSLProgram::setVec4(std::string& name, const glm::vec4& vec) {
    auto location = getVarLocation(name);
    if (location != (unsigned int)-1) {
        glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
    }
}

void GLSLProgram::setMatrix(std::string& name, const glm::mat4& mat) {
    auto location = getVarLocation(name);
    if (location != (unsigned int)-1) {
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    }
}
