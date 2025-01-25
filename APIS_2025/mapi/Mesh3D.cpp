#include "Mesh3D.h"

int Mesh3D::nextId = 1;

Mesh3D::Mesh3D()
	: meshID(nextId++),
	colorRGBA(1.0f, 1.0f, 1.0f, 1.0f),
	vVertList()
{}

int Mesh3D::getMeshId() const
{
	return meshID;
}

const vector<vertex_t>* Mesh3D::getVertexList() const
{
	return &vVertList;
}


void Mesh3D::addVertex(const vertex_t& vertex)
{
	vVertList.push_back(vertex);
}
