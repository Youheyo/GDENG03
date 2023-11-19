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

void AGameObject::setName(std::string name)
{
	this->name = name;
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
	this->position = Vector3D(x, y, z);
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
    this->scale = Vector3D(x, y, z);
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
    this->rotation = Vector3D(x, y, z);
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

void AGameObject::updateMatrix()
{
	Matrix4x4 temp; temp.setIdentity();
	// * Scale
	Matrix4x4 scaleMat; scaleMat.setScale(this->scale);
	temp *= scaleMat;

	// * Rotation XYZ
	Matrix4x4 rotMat; rotMat.setIdentity();
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.getX());
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.getY());
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.getZ());
	rotMat = rotMat.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));
	temp *= rotMat;

	// * Translate
	Matrix4x4 transMat; transMat.setTranslation(this->position);
	temp *= transMat;

	this->localMatrix = temp;

}

void AGameObject::recomputeMatrix(float matrix[16])
{
	float matrix4x4[4][4];
	matrix4x4[0][0] = matrix[0];
	matrix4x4[0][1] = matrix[1];
	matrix4x4[0][2] = matrix[2];
	matrix4x4[0][3] = matrix[3];

	matrix4x4[1][0] = matrix[4];
	matrix4x4[1][1] = matrix[5];
	matrix4x4[1][2] = matrix[6];
	matrix4x4[1][3] = matrix[7];

	matrix4x4[2][0] = matrix[8];
	matrix4x4[2][1] = matrix[9];
	matrix4x4[2][2] = matrix[10];
	matrix4x4[2][3] = matrix[11];

	matrix4x4[3][0] = matrix[12];
	matrix4x4[3][1] = matrix[13];
	matrix4x4[3][2] = matrix[14];
	matrix4x4[3][3] = matrix[15];

	Matrix4x4 newMatrix; newMatrix.setMatrix(matrix4x4);
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->scale);
	Matrix4x4 transMatrix; transMatrix.setTranslation(this->position);

    // this->localMatrix = scaleMatrix * transMatrix * newMatrix;
	this->localMatrix = scaleMatrix.multiplyTo(transMatrix.multiplyTo(newMatrix));

	// ? Find a way to update position for inspector without interfering with physics
	// this->setPosition(localMatrix.getMatrix()[12], localMatrix.getMatrix()[13], localMatrix.getMatrix()[14]);
}

float* AGameObject::getPhysicsLocalMatrix() {
	
    Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity();
	translationMatrix.setTranslation(this->getPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(Vector3D::ones()); //physics 3D only accepts uniform scale for rigidbody
	Vector3D rotation = this->getRotation();
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.getX());
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.getY());
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.getZ());

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
    // rotMatrix *= xMatrix * yMatrix * zMatrix;
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	// allMatrix *= scaleMatrix * rotMatrix;
	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	// allMatrix *= translationMatrix;
	allMatrix = allMatrix.multiplyTo(translationMatrix);

	return allMatrix.getMatrix();
}
