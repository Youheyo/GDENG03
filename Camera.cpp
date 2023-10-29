#include "Camera.h"
#include <iostream>

Camera::Camera(std::string name) : GameObject(name) {
    this->setPosition(Vector3D(0, 0, -2.0f));
    InputSystem::getInstance()->addListener(this);
}

Camera::~Camera() {
    
}

void Camera::draw(float width, float height, VertexShader *vs, PixelShader *ps)
{
}

void Camera::update(float deltaTime)
{

    float x = this->position.m_x;
    float y = this->position.m_y;
    float z = this->position.m_z;

    float currSpeed = moveSpeed;

    if(InputSystem::getInstance()->isKeyDown('C')){
        currSpeed *= 10.0f;
    }
    // * Forward
    if(InputSystem::getInstance()->isKeyDown('W')){
        z += deltaTime * currSpeed;
        this->setPosition(Vector3D(x, y, z));
        this->updateViewMatrix();
    }
    // * Backward
    if(InputSystem::getInstance()->isKeyDown('S')){
        z -= deltaTime * currSpeed;
        this->setPosition(Vector3D(x, y, z));
        this->updateViewMatrix();
    }
    // * Strafe Left
    if(InputSystem::getInstance()->isKeyDown('A')){
        x -= deltaTime * currSpeed;
        this->setPosition(Vector3D(x, y, z));
        this->updateViewMatrix();
    }
    // * Strafe Right
    if(InputSystem::getInstance()->isKeyDown('D')){
        x += deltaTime * currSpeed;
        this->setPosition(Vector3D(x, y, z));
        this->updateViewMatrix();
    }
    if(InputSystem::getInstance()->isKeyDown('Q')){
        y += deltaTime * currSpeed;
        this->setPosition(Vector3D(x, y, z));
        this->updateViewMatrix();
    }
    if(InputSystem::getInstance()->isKeyDown('E')){
        y -= deltaTime * currSpeed;
        this->setPosition(Vector3D(x, y, z));
        this->updateViewMatrix();
    }
}

Matrix4x4 Camera::getViewMatrix() {
    return this->localMatrix;
}

void Camera::updateViewMatrix()
{

    Matrix4x4 worldCam, temp; 
    worldCam.setIdentity();

    temp.setIdentity();
    temp.setRotationX(this->rotation.m_x);
    worldCam *= temp;

    temp.setIdentity();
    temp.setRotationY(this->rotation.m_y);
    worldCam *= temp;

    temp.setIdentity();
    temp.setRotationZ(this->rotation.m_z);
    worldCam *= temp;

    temp.setIdentity();
    temp.setTranslation(this->position);
    worldCam *= temp;

    worldCam.getInverse();
    this->localMatrix = worldCam;
}

void Camera::onKeyDown(int key) {
    
}

void Camera::onKeyUp(int key) {
    
}

void Camera::onMouseMove(const Point deltaPos) {


		float speed = 0.001f;

        float x = this->rotation.m_x;
        float y = this->rotation.m_y;
        float z = this->rotation.m_z;

		this->setRotation(Vector3D(x + deltaPos.getY() * speed, y + deltaPos.getX() * speed, z));

		this->updateViewMatrix();
	
}
void Camera::onLeftMouseDown(const Point deltaPos) {
    
}

void Camera::onLeftMouseUp(const Point deltaPos) {
    
}

void Camera::onRightMouseUp(const Point deltaPos) {
    
}

void Camera::onRightMouseDown(const Point deltaPos) {
    
}
