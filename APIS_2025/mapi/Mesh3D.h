#include "vertex.h"
#pragma once
using namespace std;

class Mesh3D
{
private:
	static int nextId;
	int meshID;
	glm::vec4 colorRGBA;
	vector<vertex_t> vVertList;
public:
	Mesh3D();

	//Getters
	int getMeshId() const;
	const vector<vertex_t>* getVertexList() const;

	//Métodos
	void addVertex(const vertex_t& vertex);
};