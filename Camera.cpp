#include "Camera.h"
#include <iostream>

Camera::Camera(std::string name) {
    this->setPosition(Vector3D(0,0,-4));
	this->localMatrix.setIdentity();
    this->updateViewMatrix();
    InputSystem::getInstance()->addListener(this);
}

Camera::~Camera() {
    
}

void Camera::update(float deltaTime) {
    
    Vector3D localPos = this->position;

    float x = localPos.m_x;
    float y = localPos.m_y;
    float z = localPos.m_z;

    float moveSpeed = 10.0f;

    if(InputSystem::getInstance()->isKeyDown('W')){
        std::cout << "Camera Moving... " << this->position.m_x << " / " << this->position.m_y << " / " << this->position.m_z << std::endl;
        z += deltaTime * moveSpeed;
        this->setPosition(Vector3D(x, y, z));
        this->updateViewMatrix();
    }
    else if(InputSystem::getInstance()->isKeyDown('S')){
        std::cout << "Camera Moving... " << this->position.m_x << " / " << this->position.m_y << " / " << this->position.m_z << std::endl;
        z -= deltaTime * moveSpeed;
        this->setPosition(Vector3D(x, y, z));
        this->updateViewMatrix();
    }
    else if(InputSystem::getInstance()->isKeyDown('A')){
        std::cout << "Camera Moving... " << this->position.m_x << " / " << this->position.m_y << " / " << this->position.m_z << std::endl;
        x += deltaTime * moveSpeed;
        this->setPosition(Vector3D(x, y, z));
        this->updateViewMatrix();
    }
    else if(InputSystem::getInstance()->isKeyDown('D')){
        x -= deltaTime * moveSpeed;
        std::cout << "Camera Moving... " << this->position.m_x << " / " << this->position.m_y << " / " << this->position.m_z << std::endl;
        this->setPosition(Vector3D(x, y, z));
        this->updateViewMatrix();
    }

    // std::cout << this->position.m_x << " - "  << this->position.m_y << " - " << this->position.m_z  << std::endl; 

}

Matrix4x4 Camera::getViewMatrix() {
    return this->localMatrix;
}

void Camera::updateViewMatrix()
{

    Matrix4x4 worldCam; worldCam.setIdentity();
    Matrix4x4 temp; temp.setIdentity();

    Vector3D localrot = this->rotation;

    temp.setRotationX(localrot.m_x);
    worldCam *= temp;

    temp.setRotationY(localrot.m_y);
    worldCam *= temp;

    temp.setRotationZ(localrot.m_z);
    worldCam *= temp;

    worldCam.getInverse();
    this->localMatrix = worldCam;
}

void Camera::onKeyDown(int key) {
    
}

void Camera::onKeyUp(int key) {
    
}

void Camera::onMouseMove(const Point deltaPos) {


		float speed = 1.0f;

		this->setRotation(Vector3D(this->rotation.m_x + deltaPos.getX() * speed, this->rotation.m_y + deltaPos.getY() * speed, this->rotation.m_z));
        std::cout << "Mouse Rotation " << this->rotation.m_x << " - "  << this->rotation.m_y << " - " << this->rotation.m_z  << std::endl; 

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
