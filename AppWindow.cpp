#include "AppWindow.h"
#include <Windows.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

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


void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();	

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	
	GraphicsEngine::get()->releaseCompiledShader();	

    constant cc;
	cc.m_time = 0;

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	for(curr_amt; curr_amt < target_amt; curr_amt++){

	//float random_float = -1.0 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1 - -1.0f)));
		Cube* cube = new Cube(shader_byte_code, size_shader);
		cube->setPosition(Vector3D(2,2,0));
		cube->setScale(Vector3D(.5f,.5f,.5f));
		cube->setRotation(Vector3D(1,0,0));
		this->object_list.push_back(cube);

	}
		m_cb = GraphicsEngine::get()->createConstantBuffer();
		m_cb->load(&cc, sizeof(constant));

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	// * Clear Render Target
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, .6f, 0, 1, 1);

	// * Set Viewport of rendertarget
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(getWidth(), getHeight());

	// * Set Default Shader in Graphics Pipeline 
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	for(int x = 0; x < object_list.size(); x++){
		object_list[x]->update(EngineTime::getDeltaTime());
		object_list[x]->draw(getWidth(), getHeight(), nullptr, 0);
	}
	
	m_swap_chain->present(false);

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
	GraphicsEngine::get()->release();

}

LONG AppWindow::getWidth()
{
	RECT rc = this->getClientWindowRect();
    return  (rc.right - rc.left);
}

LONG AppWindow::getHeight()
{
    RECT rc = this->getClientWindowRect();
    return  (rc.bottom - rc.top);
}

