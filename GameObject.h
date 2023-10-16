#pragma once
#include "Vector3D.h"
#include "Matrix4x4.h"

class GameObject{

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

    GameObject();
    ~GameObject();

    virtual void update(float deltaTime);
    virtual void draw(float width, float height, void* shader_byte_code, size_t size_shader);
    
public:
    void setPosition(Vector3D pos);
    Vector3D getPosition();

    void setScale(Vector3D scale);

    void setRotation(Vector3D rot);

    
protected:

    Vector3D position;
    Vector3D scale;
    Vector3D rotation;
    Matrix4x4 localMatrix;
};