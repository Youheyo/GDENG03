#pragma once
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include <string>

class AGameObject{

public:

struct vertex {
	Vector3D color;
	Vector3D color1;

	Vector3D position;
};

__declspec(align(16))
struct constant{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};

    AGameObject(std::string name);
    ~AGameObject();

    std::string getName();
    virtual void update(float deltaTime) = 0;
    virtual void draw(float width, float height, VertexShader *vs, PixelShader *ps) = 0;
    
public:
    void setPosition(Vector3D pos);
    void setPosition(float x, float y, float z);
    Vector3D getPosition();

    void setScale(Vector3D scale);
    void setScale(float x, float y, float z);
    Vector3D getScale();

    void setRotation(Vector3D rot);
    void setRotation(float x, float y, float z);
    Vector3D getRotation();

    void recomputeMatrix(float matrix[16]);
    
    float* getPhysicsLocalMatrix();

	bool canAnimate = false;
    void setEnabled(bool enable);
    bool isEnabled();
    
protected:

    std::string name;
    bool enabled = true;

    Vector3D position;
    Vector3D scale;
    Vector3D rotation;
    Matrix4x4 localMatrix;
};