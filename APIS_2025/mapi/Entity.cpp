#include "Entity.h"

//Constructor
Entity::Entity()
	: pos(0.0f), rot(0.0f), scale(1.0f), model(1.0f)
{
}

// Getters
glm::vec4 Entity::getPosition() const
{
	return this->pos;
}

glm::vec4 Entity::getRotation() const
{
	return this->rot;
}

glm::vec4 Entity::getScale() const
{
	return this->scale;
}

const glm::mat4& Entity::getModel() const {
	return model;
}

// Setters

void Entity::setPosition(glm::vec4 pos)
{
	this->pos = pos;
}

void Entity::setRotation(glm::vec4 rot)
{
	this->rot = rot;
}

void Entity::setScale(glm::vec4 scale)
{
	this->scale = scale;
}

// Métodos

void Entity::computeModelMatrix()
{
	// Primero la igualamos a la matriz Identidad
	model = glm::mat4(1);

	//Aplicamos traslacion
	model = glm::translate(model, glm::vec3(pos));

	// Aplicamos rotación
	model = glm::rotate(model, rot.x, { 1.0f, 0.0f, 0.0f });
	model = glm::rotate(model, rot.y, { 0.0f, 1.0f, 0.0f });
	model = glm::rotate(model, rot.z, { 0.0f, 0.0f, 1.0f });

	//Aplicamos Escalado
	model = glm::scale(model, glm::vec3(scale));
}