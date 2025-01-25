#pragma once
#include "vertex.h"
#include "Entity.h"
#include "Mesh3D.h"

using namespace std;

enum class ObjectType {
	Object1,
	Object2,
	Object3,
	Object4
};

class Object : public Entity
{
	protected:
		Mesh3D* mesh;
		ObjectType tipo;
	public:
		// Constructor
        Object();
        virtual ~Object();

		// Getters
        Mesh3D* getMesh() const;
		int getTipo() const;

		// Setters
        void setMesh(Mesh3D* mesh);
        void setTipo(int tipo);

		// Métodos
        virtual void loadDataFromFile(const std::string& file) = 0;
};

