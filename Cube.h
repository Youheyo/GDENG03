#pragma once
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "ConstantBuffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "EngineTime.h"
#include "SceneCameraHandler.h"

class Cube : public AGameObject{

public:
    Cube(std::string name, void *shader_byte_code, size_t size_shader);
    ~Cube();

    void update(float deltaTime) override;
	void draw(float width, float height, VertexShader *vs, PixelShader *ps) override;

	void setSpeed(float speed);
	void setRotAx(char ax);

private:

	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexShader* vs;
	PixelShader* ps;
	ConstantBuffer* cb;

    vertex vertex_list[8] = {
		// ? Front Face
		{ Vector3D(-0.5f,-0.5f,-0.5f),	Vector3D( 1,0,0), Vector3D(0.2f,0,0)},
		{ Vector3D(-0.5f,0.5f,-0.5f),  	Vector3D( 1,1,0), Vector3D(0.2f,0.2f,0)},
		{ Vector3D(0.5f, 0.5f,-0.5f),  	Vector3D( 1,1,0), Vector3D(0.2f,0.2f,0)},
		{ Vector3D(0.5f, -0.5f,-0.5f), 	Vector3D( 1,0,0), Vector3D(0.2f,0,0)},

		// ? Back Face
		{ Vector3D(0.5f,-0.5f,0.5f),	Vector3D( 0,1,0), Vector3D(0,0.2f,0)},
		{ Vector3D(0.5f,0.5f,0.5f), 	Vector3D( 0,1,1), Vector3D(0,0.2f,0.2f)},
		{ Vector3D(-0.5f,0.5f,0.5f), 	Vector3D( 0,1,1), Vector3D(0,0.2f,0.2f)},
		{ Vector3D(-0.5f,-0.5f,0.5f), 	Vector3D( 1,0,1), Vector3D(0,0.2f,0)},
	};

    unsigned int index_list[36] = {
		// ? Front Side
		0,1,2, // First Triangle
		2,3,0, // Second Triangle
		// ? Back Side
		4,5,6,
		6,7,4,
		// ? Top Side
		1,6,5,
		5,2,1,
		// ? Bottom Side
		7,0,3,
		3,4,7,
		// ? Right Side
		3,2,5,
		5,4,3,
		// ? Left Side
		7,6,1,
		1,0,7
	};

	float m_delta_time = 0;
	float m_delta_pos = 0;

	bool reverse = false;
	int ax_x = 0, ax_y = 0,ax_z = 0;
	float rot_speed = 1;
};