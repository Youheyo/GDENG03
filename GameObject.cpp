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
    std::cout << "Position set to:" << std::endl;
    std::cout << "X:" << this->position.m_x << std::endl; 
    std::cout << "Y:" << this->position.m_y << std::endl; 
    std::cout << "Z:" << this->position.m_z << std::endl << std::endl; 
}

void GameObject::setScale(Vector3D scale) {
    this->scale = scale;
    // std::cout << "Scale set to:" << std::endl;
    // std::cout << "X:" << this->scale.m_x << std::endl; 
    // std::cout << "Y:" << this->scale.m_y << std::endl; 
    // std::cout << "Z:" << this->scale.m_z << std::endl << std::endl; 
}

void GameObject::setRotation(Vector3D rot) {
    this->rotation = rot;    
    // std::cout << "Roation set to:" << std::endl;
    // std::cout << "X:" << this->rotation.m_x << std::endl; 
    // std::cout << "Y:" << this->rotation.m_y << std::endl; 
    // std::cout << "Z:" << this->rotation.m_z << std::endl << std::endl; 
}
