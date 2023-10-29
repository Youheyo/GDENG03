#include "GameObject.h"
#include <iostream>

GameObject::GameObject(std::string name)
{
    this->name = name;
    this->position = Vector3D(0,0,0);
    this->scale = Vector3D(1,1,1);
    this->rotation = Vector3D(0,0,0);

}

GameObject::~GameObject() {
    
}

std::string GameObject::getName()
{
    return this->name;
}

void GameObject::update(float deltaTime)
{
}

void GameObject::draw(float width, float height, VertexShader *vs, PixelShader *ps)
{
}

void GameObject::setPosition(Vector3D pos)
{
    this->position = pos;
}

void GameObject::setPosition(float x, float y, float z)
{
    this->position.m_x = x;
    this->position.m_y = y;
    this->position.m_z = z;
}

Vector3D GameObject::getPosition()
{
    return this->position;
}

void GameObject::setScale(Vector3D scale)
{
    this->scale = scale;
}

void GameObject::setScale(float x, float y, float z)
{
    this->scale.m_x = x;
    this->scale.m_y = y;
    this->scale.m_z = z;
}

void GameObject::setRotation(Vector3D rot)
{
    this->rotation = rot;
}

void GameObject::setRotation(float x, float y, float z)
{
    this->rotation.m_x = x;    
    this->rotation.m_y = y;    
    this->rotation.m_z = z;
}
