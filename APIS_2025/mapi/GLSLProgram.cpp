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
        std::cout << "ERROR: variable " << varName <<
            " no encontrada en shader\n";
        return -1;
    }
}


// ---------- SETTERS: setInt, setFloat, setVec3, setVec4, setMatrix -----------
void GLSLProgram::setInt(string& name, int val) {
    auto loc = getVarLocation(name);
    if (loc != (unsigned int)-1) {
        glUniform1i(loc, val);
    }
}

void GLSLProgram::setFloat(std::string& name, float val) {
    auto loc = getVarLocation(name);
    if (loc != (unsigned int)-1) {
        glUniform1f(loc, val);
    }
}

void GLSLProgram::setVec3(std::string& name, const glm::vec3& vec) {
    auto loc = getVarLocation(name);
    if (loc != (unsigned int)-1) {
        glUniform3f(loc, vec.x, vec.y, vec.z);
    }
}

void GLSLProgram::setVec4(std::string& name, const glm::vec4& vec) {
    auto loc = getVarLocation(name);
    if (loc != (unsigned int)-1) {
        glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
    }
}

void GLSLProgram::setMatrix(std::string& name, const glm::mat4& mat) {
    auto loc = getVarLocation(name);
    if (loc != (unsigned int)-1) {
        glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
    }
}
