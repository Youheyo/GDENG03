#include "Camera.h"
#include "InputSystem.h"
#include <iostream>

Camera::Camera(std::string name) : AGameObject(name)
{
	this->forwardDirection = Vector3D(1.0f, 0.0f, 1.0f);
	this->backwardDirection = Vector3D(-1.0f, 0.0f, -1.0f);

	this->setPosition(0.0f, 0.0f, -4.0f);
	//this->worldCameraMatrix.setTranslation(this->getLocalPosition());
	this->updateViewMatrix();
	InputSystem::getInstance()->addListener(this);
}

Camera::~Camera()
{
	InputSystem::getInstance()->removeListener(this);
}

void Camera::update(float deltaTime)
{
	Vector3D localPos = this->getPosition();
	float x = localPos.getX();
	float y = localPos.getY();
	float z = localPos.getZ();
	float moveSpeed = 10.0f;

	if (InputSystem::getInstance()->isKeyDown('W')) {
		//std::cout << "W...\n";
		Vector3D direction = localMatrix.getZDirection();
		Vector3D newPos = Vector3D(
			x + direction.getX() * deltaTime * moveSpeed,
			y + direction.getY() * deltaTime * moveSpeed,
			z + direction.getZ() * deltaTime * moveSpeed);

		this->setPosition(newPos.getX(), newPos.getY(), newPos.getZ());
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		Vector3D direction = localMatrix.getZDirection();
		Vector3D newPos = Vector3D(
			x + direction.getX() * deltaTime * -moveSpeed,
			y + direction.getY() * deltaTime * -moveSpeed,
			z + direction.getZ() * deltaTime * -moveSpeed);

		this->setPosition(newPos.getX(), newPos.getY(), newPos.getZ());
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		Vector3D direction = localMatrix.getXDirection();
		Vector3D newPos = Vector3D(
			x + direction.getX() * deltaTime * -moveSpeed,
			y + direction.getY() * deltaTime * -moveSpeed,
			z + direction.getZ() * deltaTime * -moveSpeed);

		this->setPosition(newPos.getX(), newPos.getY(), newPos.getZ());
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		Vector3D direction = localMatrix.getXDirection();
		Vector3D newPos = Vector3D(
			x + direction.getX() * deltaTime * moveSpeed,
			y + direction.getY() * deltaTime * moveSpeed,
			z + direction.getZ() * deltaTime * moveSpeed);

		this->setPosition(newPos.getX(), newPos.getY(), newPos.getZ());
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('Q')) {
		Vector3D direction = Vector3D(0, 1, 0);
		Vector3D newPos = Vector3D(
			x + direction.getX() * deltaTime * -moveSpeed,
			y + direction.getY() * deltaTime * -moveSpeed,
			z + direction.getZ() * deltaTime * -moveSpeed);

		this->setPosition(newPos.getX(), newPos.getY(), newPos.getZ());
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('E')) {
		Vector3D direction = Vector3D(0, 1, 0);
		Vector3D newPos = Vector3D(
			x + direction.getX() * deltaTime * moveSpeed,
			y + direction.getY() * deltaTime * moveSpeed,
			z + direction.getZ() * deltaTime * moveSpeed);

		this->setPosition(newPos.getX(), newPos.getY(), newPos.getZ());
		this->updateViewMatrix();
	}
	//std::cout << "Camera Rotation: [" << this->rotation.m_x << ", " << this->rotation.m_y << ", " << this->rotation.m_z << "]\n";
}

void Camera::draw(float width, float height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	// no-op
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->viewMatrix;
}

void Camera::onKeyDown(int key)
{
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const Point deltaPos)
{
	if (this->mouseDown && this->canMouseMove) {
		float speed = 0.001f;

		float x = this->rotation.getX();
		float y = this->rotation.getY();
		float z = this->rotation.getZ();

		this->setRotation(Vector3D(x + deltaPos.getY() * speed, y + deltaPos.getX() * speed, z));

		this->updateViewMatrix();
	}
}

void Camera::onLeftMouseDown(const Point deltaPos)
{
}

void Camera::onLeftMouseUp(const Point deltaPos)
{
}

void Camera::onRightMouseDown(const Point deltaPos)
{
	this->mouseDown = true;
}

void Camera::onRightMouseUp(const Point deltaPos)
{
	this->mouseDown = false;
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam; worldCam.setIdentity();
	Matrix4x4 temp; temp.setIdentity();

	Vector3D localRot = this->getRotation();

	temp.setRotationX(localRot.getX());
	worldCam *= temp;

	temp.setRotationY(localRot.getY());
	worldCam *=temp;

	temp.setTranslation(this->getPosition());
	worldCam *= temp;

	this->localMatrix = worldCam;

	worldCam.getInverse();

	this->viewMatrix = worldCam;
}

void Camera::savePerspectiveView()
{
    this->perspectivePos = this->getPosition();
    this->perspectiveRot = this->getRotation();
}

void Camera::setPerspectiveView()
{
	this->canMouseMove = true;
	this->setPosition(this->perspectivePos);
	this->setRotation(this->perspectiveRot);
	this->updateViewMatrix();
}

void Camera::setTopDownView()
{
	this->canMouseMove = false;
	savePerspectiveView();
    this->setPosition(Vector3D(0, 10, 0));
	this->setRotation(Vector3D(0.9, 0, 0));
	this->updateViewMatrix();
}
