#include "Object3D.h"
#include <iostream>
#include "pugixml.hpp"
#include "common.h"

using namespace std;

// Constructor
Object3D::Object3D() : Object() 
{
    //PARA PRÁCTICA 3
    //loadFromFile(filename);
}

// Destructor
Object3D::~Object3D() {}

void Object3D::loadDataFromFile(const string& file) {
    std::cout << "TO-DO: Cargando datos " << file << std::endl;

    /*
    // EJEMPLO CLASE PARA PRÁCTICA 3

    // Abrir archivos .mesh -> librería xml
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file.c_str());

    if (result) {
        //Cargado correctamente, odemos analizar su contenido ....

        //Buscar nodo mesh
        pugi::xml_node meshNode = doc.child("mesh");
        pugi::xml_node buffersNode = meshNode.child("buffers");

        for (pugi::xml_node bufferNode = bufferNode.child("buffer");
            bufferNode;
            bufferNode = bufferNode.next_sibling("buffer"))
        {
            Mesh3D* m = new Mesh3D();
            //Iteramos por todos los mesh
            auto materialNode = bufferNode.child("material");
            string textureName = materialNode.child("texture").child("layer").text().as_string();
                if (string(materialNode.child("texture").attribute("type").as_string())
                    == "color2D")
                {
                    m->text = newTexture();
                    m->text->loadFile(textureName);
                    m->text->update();
                }

                auto shaderList = splitString<string>(materialNode.child("shader").text(), ','); //funcion en common que diveide los ficehros shader divididos por,
                m->prog = new GLProgram();
                m->prog->addPrograms(shaderList);
                m->prog->readVarList();

                loadObj(bufferNode.child("meshData").text().as_string(), m);

                //copy pasrte diapo 19 tema 5 -->para la practica ; en if key == f no usamos normales  comentar esa parte
                //copyPaste loadObj -> método en esta clase
        }
    }
    else {
        std::cout << result.description() << file << std::endl;

    }
    */


}