#include "AGameObject.h"
#include <iostream>

AGameObject::AGameObject(std::string name)
{
    this->name = name;
    this->position = Vector3D(0,0,0);
    this->scale = Vector3D(1,1,1);
    this->rotation = Vector3D(0,0,0);

}

AGameObject::~AGameObject() {
    
}

std::string AGameObject::getName()
{
    return this->name;
}

void AGameObject::update(float deltaTime)
{

}

void AGameObject::draw(float width, float height, VertexShader *vs, PixelShader *ps)
{
}

void AGameObject::setPosition(Vector3D pos)
{
    this->position = pos;
}

void AGameObject::setPosition(float x, float y, float z)
{
    this->position.m_x = x;
    this->position.m_y = y;
    this->position.m_z = z;
}

Vector3D AGameObject::getPosition()
{
    return this->position;
}

void AGameObject::setScale(Vector3D scale)
{
    this->scale = scale;
}

void AGameObject::setScale(float x, float y, float z)
{
    this->scale.m_x = x;
    this->scale.m_y = y;
    this->scale.m_z = z;
}

Vector3D AGameObject::getScale()
{
    return this->scale;
}

void AGameObject::setRotation(Vector3D rot)
{
    this->rotation = rot;
}

void AGameObject::setRotation(float x, float y, float z)
{
    this->rotation.m_x = x;    
    this->rotation.m_y = y;    
    this->rotation.m_z = z;
}

Vector3D AGameObject::getRotation()
{
    return this->rotation;
}

void AGameObject::setEnabled(bool enable)
{
    this->enabled = enable;
}

bool AGameObject::isEnabled()
{
    return this->enabled;
}
