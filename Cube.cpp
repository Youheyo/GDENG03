#include "Cube.h"
#include <iostream>

Cube::Cube(void *shader_byte_code, size_t size_shader) {
    
	this->vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	this->vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	this->vb->load(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();	

	this->ib = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);
	this->ib->load(index_list, size_index_list);

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	this->ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	
	GraphicsEngine::get()->releaseCompiledShader();	

    constant cc;
	cc.m_time = 0;

	this->cb = GraphicsEngine::get()->createConstantBuffer();
	this->cb->load(&cc, sizeof(constant));

}

Cube::~Cube() {
    this->vb->release();
	this->ib->release();
	this->ps->release();
	this->cb->release();
}

void Cube::update(float deltaTime) {

	m_delta_time += deltaTime;
	m_delta_pos += deltaTime / 10.0f;
	
	this->setRotation(Vector3D(m_delta_time * rot_speed * ax_x, m_delta_time * rot_speed * ax_y, m_delta_time * rot_speed * ax_z));


	if(m_delta_pos > 1.0f) m_delta_pos = 0;
}

void Cube::draw(float width, float height, void *shader_byte_code, size_t size_shader)
{
	constant cc;
	// cc.m_world.setScale(Vector3D(this->scale));

	this->localMatrix.setIdentity();
	this->localMatrix.setScale(this->scale);
	cc.m_world*=this->localMatrix;

	this->localMatrix.setIdentity();
	this->localMatrix.setRotationZ(this->rotation.m_z);
	cc.m_world*=this->localMatrix;

	this->localMatrix.setIdentity();
	this->localMatrix.setRotationY(this->rotation.m_y);
	cc.m_world*=this->localMatrix;

	this->localMatrix.setIdentity();
	this->localMatrix.setRotationX(this->rotation.m_x);
	cc.m_world*=this->localMatrix;

	this->localMatrix.setIdentity();
	this->localMatrix.setScale(this->scale);
	cc.m_world*=this->localMatrix;

	this->localMatrix.setIdentity();
	this->localMatrix.setTranslation(this->position);
	cc.m_world*=this->localMatrix;

	Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cc.m_view = cameraMatrix;

	cc.m_proj.setPerspectiveFovLH(
	        (width) / 300.0f,
	        (height) / 300.0f,
	        1.0f,
	        1000.0f
	);

	// cc.m_view.setIdentity();
	// cc.m_proj.setOrthoLH(
	// 	(width) / 300.0f,
	// 	(height) / 300.0f,
	// 	-4.0f,
	// 	4.0f
	// );

    GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(this->vs, this->cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(this->ps, this->cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(this->vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(this->ps);

	// * Set Vertices of triangle to draw
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->vb);
	// * Set Indices of triangle to draw
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(this->ib);


	// * Draw triangle
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(this->ib->getSizeIndexList(),0, 0);

	this->cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

}

void Cube::setSpeed(float speed) {
    this->rot_speed = speed;
}

void Cube::setRotAx(char ax) {
    switch (ax){
		case 'x':
			ax_x = 1;
			break;
		case 'y':
			ax_y = 1;
			break;
		case 'z':
			ax_z = 1;
			break;
	}
}