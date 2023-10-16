#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
    this->position = Vector3D(0,0,0);
    this->scale = Vector3D(1,1,1);
    this->rotation = Vector3D(0,0,0);
}

GameObject::~GameObject() {
    
}

void GameObject::update(float deltaTime)
{
}

void GameObject::draw(float width, float height, void *shader_byte_code, size_t size_shader)
{
}


void GameObject::setPosition(Vector3D pos) {
    this->position = pos;
}

Vector3D GameObject::getPosition()
{
    return this->position;
}

void GameObject::setScale(Vector3D scale) {
    this->scale = scale;
}

void GameObject::setRotation(Vector3D rot) {
    this->rotation = rot;    
}
