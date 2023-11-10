#include "Cube.h"
#include <iostream>

Cube::Cube(std::string name, void *shader_byte_code, size_t size_shader) : GameObject(name) {
    
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
	GameObject::~GameObject();
}

void Cube::update(float deltaTime) {
#if 0
	if(InputSystem::getInstance()->isKeyDown('S')){
		m_delta_time += deltaTime;
		m_delta_pos += deltaTime / 10.0f;
		
		this->setRotation(Vector3D(m_delta_time * rot_speed * ax_x, m_delta_time * rot_speed * ax_y, m_delta_time * rot_speed * ax_z));


		if(m_delta_pos > 1.0f) m_delta_pos = 0;
	}
	else if(InputSystem::getInstance()->isKeyDown('W')){
		m_delta_time -= deltaTime;
		m_delta_pos -= deltaTime / 10.0f;
		
		this->setRotation(Vector3D(m_delta_time * rot_speed * ax_x, m_delta_time * rot_speed * ax_y, m_delta_time * rot_speed * ax_z));


		if(m_delta_pos > 1.0f) m_delta_pos = 0;
	}
#elif 0
	if(canAnimate){
		m_delta_time += deltaTime;
		m_delta_pos += deltaTime;
		if(m_delta_pos >= 1) {
				m_delta_pos = 0;
		}
		this->setRotation(Vector3D(m_delta_time * rot_speed * ax_x, m_delta_time * rot_speed * ax_y, m_delta_time * rot_speed * ax_z));
	}
#endif
}

void Cube::draw(float width, float height,  VertexShader *vs, PixelShader *ps)
{
	if(!this->enabled) return;

	constant cc;
	cc.m_world.setIdentity();
	Matrix4x4 temp;

	cc.m_time = ::GetTickCount();

	// * Scale
	temp.setScale(this->scale);
	cc.m_world*=temp;

	// * Rotation XYZ
	temp.setRotationZ(this->rotation.m_z);
	cc.m_world*=temp;

	temp.setRotationY(this->rotation.m_y);
	cc.m_world*=temp;

	temp.setRotationX(this->rotation.m_x);
	cc.m_world*=temp;

	// * Translate
	temp.setTranslation(this->position);
	cc.m_world*=temp;


	Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cc.m_view = cameraMatrix;

	cc.m_proj.setPerspectiveFovLH(
			1.57f,
			(width / height),
	        0.1f,
	        100.0f
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

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(ps);

	// * Set Vertices of triangle to draw
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->vb);
	// * Set Indices of triangle to draw
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(this->ib);

	// * Draw triangle
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(this->ib->getSizeIndexList(),0, 0);
	// GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(this->ib->getSizeIndexList(),0);



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
		case 'a':
			ax_x = 1;
			ax_y = 1;
			ax_z = 1;
			break;
		default:
			ax_x = 0;
			ax_y = 0;
			ax_z = 0;
	}
}
