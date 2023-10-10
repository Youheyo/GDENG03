#include "AppWindow.h"
#include <Windows.h>
#include <iostream>

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

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::updateQuadPosition()
{
	constant cc;
	cc.m_time = ::GetTickCount();

	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f) {
		m_delta_pos = 0;
	}
	Matrix4x4 temp;

	//cc.m_world.setTranslation(Vector3D::lerp(Vector3D(-2,-2,0), Vector3D(2,2,0), m_delta_pos));
	
	m_delta_scale += m_delta_time / 0.55f;

	// cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));
	
	// temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f,1.5f, 0), m_delta_pos));

	// cc.m_world *= temp;

	cc.m_world.setScale(Vector3D(1,1,1));
	
	temp.setIdentity();
	temp.setRotationZ(m_delta_scale);
	cc.m_world*=temp;

	temp.setIdentity();
	temp.setRotationY(m_delta_scale);
	cc.m_world*=temp;

	temp.setIdentity();
	temp.setRotationX(m_delta_scale);
	cc.m_world*=temp;


	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH(
		(this->getClientWindowRect().right - this->getClientWindowRect().left) / 300.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 300.0f,
		-4.0f,
		4.0f
	);

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex vertex_list[] = {
		// ? Front Face
		{Vector3D(-0.5f,-0.5f,-0.5f),	Vector3D(1,0,0), Vector3D(0,1,0)},
		{Vector3D(-0.5f,0.5f,-0.5f), 	 	Vector3D( 0,1,0),Vector3D(1,1,0)},
		{ Vector3D(0.5f,0.5f,-0.5f),  	Vector3D( 0,0,1),Vector3D(1,0,0)},
		{ Vector3D(0.5f,-0.5f,-0.5f), 	Vector3D( 1,1,0), Vector3D(0,0,1)},

		// ? Back Face
		{ Vector3D(0.5f,-0.5f,0.5f),	Vector3D(1,0,0), Vector3D(0,1,0)},
		{ Vector3D(0.5f,0.5f,0.5f), 	Vector3D( 0,1,0),Vector3D(1,1,0)},
		{ Vector3D(-0.5f,0.5f,0.5f), 	Vector3D( 0,0,1),Vector3D(1,0,0)},
		{ Vector3D(-0.5f,-0.5f,0.5f), 	Vector3D( 1,1,0), Vector3D(0,0,1)}
	};

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);

	unsigned int index_list[] = {
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

	m_ib = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->load(index_list, size_index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	m_vb->load(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();	

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	
	GraphicsEngine::get()->releaseCompiledShader();	

	constant cc;
	cc.m_time = 0;


	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	// * Clear Render Target
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, .6f, 0, 1, 1);

	// * Set Viewport of rendertarget
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);


	updateQuadPosition();

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	// * Set Default Shader in Graphics Pipeline 
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	// * Set Vertices of triangle to draw
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	// * Set Indices of triangle to draw
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);


	// * Draw triangle
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(),0, 0);

	m_swap_chain->present(false);

	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();

	m_delta_time = (m_old_delta)?((m_new_delta - m_old_delta) / 1000.0f):0;

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_ib->release();
	m_cb->release();

	m_swap_chain->release();
	
	m_vs->release();
	m_ps->release();
	

	InputSystem::destroy();
	GraphicsEngine::get()->release();

}

void AppWindow::onKeyDown(int key)
{
	if(InputSystem::getInstance()->isKeyDown('W')){
		std::cout << "W Presssed\n";
	}
}

void AppWindow::onKeyUp(int key)
{
	if(InputSystem::getInstance()->isKeyDown('W')){
		std::cout << "W Released\n";
	}
}

void AppWindow::onMouseMove(const Point deltaPos)
{
}

void AppWindow::onLeftMouseDown(const Point deltaPos)
{
}

void AppWindow::onLeftMouseUp(const Point deltaPos)
{
}

void AppWindow::onRightMouseDown(const Point deltaPos)
{
}

void AppWindow::onRightMouseUp(const Point deltaPos)
{
}
