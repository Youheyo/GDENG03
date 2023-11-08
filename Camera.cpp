#include "Camera.h"
#include <iostream>

Camera::Camera(std::string name) : GameObject(name) {
    this->setPosition(Vector3D(0, 0, -2.0f));
    InputSystem::getInstance()->addListener(this);
}

Camera::~Camera() {
    InputSystem::getInstance()->removeListener(this);
}

void Camera::draw(float width, float height, VertexShader *vs, PixelShader *ps)
{
}

void Camera::update(float deltaTime)
{

    float currSpeed = moveSpeed;

    if(InputSystem::getInstance()->isKeyDown('C')){
        currSpeed *= 10.0f;
    }
    // * Forward
    if(InputSystem::getInstance()->isKeyDown('W')){
        this->m_cam_forward = 1.0;
        this->updateViewMatrix();
    }
    // * Backward
    if(InputSystem::getInstance()->isKeyDown('S')){
        this->m_cam_forward = -1.0f;
        this->updateViewMatrix();
    }
    // * Strafe Left
    if(InputSystem::getInstance()->isKeyDown('A')){
        this->m_cam_rightward = -1.0f;
        this->updateViewMatrix();
    }
    // * Strafe Right
    if(InputSystem::getInstance()->isKeyDown('D')){
		this->m_cam_rightward = 1.0;
        this->updateViewMatrix();
    }
    if(InputSystem::getInstance()->isKeyDown('Q')){
        this->m_cam_upward = 1.0;
        this->updateViewMatrix();
    }
    if(InputSystem::getInstance()->isKeyDown('E')){
        this->m_cam_upward = -1.0;
        this->updateViewMatrix();
    }
}

Matrix4x4 Camera::getViewMatrix() {
    return this->m_view_cam;
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


    Vector3D new_pos = this->localMatrix.getTranslation() + worldCam.getZDirection() * (m_cam_forward * this->speed);
    new_pos = new_pos + worldCam.getXDirection() * (m_cam_rightward * this->speed);
    new_pos = new_pos + worldCam.getYDirection() * (m_cam_upward * this->speed);
    temp.setTranslation(new_pos);
    worldCam *= temp;
    this->localMatrix = worldCam;

    worldCam.getInverse();
    this->m_view_cam = worldCam;
}

void Camera::onKeyDown(int key) {
    
}

void Camera::onKeyUp(int key) {
    this->m_cam_forward = 0.0f;
    this->m_cam_rightward = 0.0f;
    this->m_cam_upward = 0.0f;
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
