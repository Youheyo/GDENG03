#include "AppWindow.h"
#include <Windows.h>
#include <iostream>

struct vec3 {
	float x, y, z;
};

struct vertex {
	// vec3 startposition;
	// vec3 endposition;
	vec3 color;
	vec3 color1;

	vec3 position;
	vec3 position1;
};

__declspec(align(16))
struct constant{
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

	// * Original
	// vertex list[] = {
	// //POS X - Y - Z			POS1 X - Y - Z			Color	Color1
	// 	{-0.5f,-0.5f,0.0f,	-0.32f, -0.11f, 0.0f, 	1,0,0,	0,1,0},
	// 	{-0.5f,0.5f,0.0f,	-0.11f, 0.78f, 0.0f, 	0,1,0,	1,1,0},
	// 	{ 0.5f,-0.5f,0.0f,	0.75f, -0.73f, 0.0f, 	0,0,1,	1,0,0},
	// 	{ 0.5f,0.5f,0.0f,	0.88f, 0.77f, 0.0f, 	1,1,0,	0,0,1}
	// };

	// Part 1
	vertex list[] = {
	//POS X - Y - Z			POS1 X - Y - Z			Color	Color1
		{-0.8f,-0.8f,0.0f,	-0.3f,-0.3f,0.0f,	1,0,0,	0,1,0},
		{-0.9f,0.5f,0.0f,	-0.1f,0.8f,0.0f,	0,1,0,	1,1,0},
		{0.8f,-0.3f,0.0f,	0.2f,-0.8f,0.0f,	0,0,1,	1,0,0},
		{-0.8f,-0.8f,0.0f,	0.8f,0.8f,0.0f,		1,1,0,	0,0,1}
	};

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// GraphicsEngine::get()->createShaders();
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	// GraphicsEngine::get()->getShadersBufferAndSize(&shader_byte_code, &size_shader);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

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

	if(this->enable_speed){

		this->elapsed_time += EngineTime::getDeltaTime();

		if(this->speed > this->max_speed){
			this->speed_up = false;
			std::cout << "SPEEDING DOWN";
		}
		else if (this->speed < this->min_speed){
			this->speed_up = true;
			std::cout << "SPEEDING UP";
		}

		if(this->speed_up){
			this->speed += EngineTime::getDeltaTime() * 10;
		}
		else{
			this->speed -= EngineTime::getDeltaTime() * 10;
		}

		std::cout << this->speed << std::endl;
	}

	Window::onUpdate();
	// * Clear Render Target
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, .6f, 0, 1, 1);

	// * Set Viewport of rendertarget
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	constant cc;

	if(!this->enable_speed) cc.m_time = ::GetTickCount();
	else cc.m_time = elapsed_time * speed;

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	// * Set Default Shader in Graphics Pipeline 
	// GraphicsEngine::get()->setShaders();
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	// * Set Vertices of triangle to draw
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// * Draw triangle
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(),0);

	m_swap_chain->present(false);

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();

}