#include "Plane.h"


Plane::Plane(std::string name, void* shader_byte_code, size_t size_shader) : Cube(name, shader_byte_code, size_shader){
    
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

	this->setScale(1.0f, 1.0f, 0.1f);
	this->setRotation(90.0f, 0.0f, 0.0f);
}

Plane::~Plane() {
    this->vb->release();
	this->ib->release();
	AGameObject::~AGameObject();
}

void Plane::update(float deltaTime) {
    
}

void Plane::draw(float width, float height, VertexShader *vs, PixelShader *ps)
{
	if(!this->enabled) return;

	constant cc;
	cc.m_world.setIdentity();
	Matrix4x4 temp;

	cc.m_time = ::GetTickCount();

	// updateMatrix();
	cc.m_world = this->localMatrix;	

	Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cc.m_view = cameraMatrix;

	cc.m_proj.setPerspectiveFovLH(
			1.57f,
			(width / height),
	        0.1f,
	        100.0f
	);

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
