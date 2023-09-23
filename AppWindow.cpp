#include "AppWindow.h"

struct vec3 {
	float x, y, z;
};

struct vertex {
	// vec3 startposition;
	// vec3 endposition;
	// color color;
	
	vec3 position;
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

	vertex list[] = {
		//X - Y - Z
		{-0.5f,-0.5f,0.0f}, // POS1
		{-0.5f,0.5f,0.0f}, // POS2
		{ 0.5f,-0.5f,0.0f },// POS2
		{ 0.5f,0.5f,0.0f}
	};

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->createShaders();
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	// GraphicsEngine::get()->getShadersBufferAndSize(&shader_byte_code, &size_shader);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();	
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	// * Clear Render Target
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 1, 0, 0, 1);

	// * Set Viewport of rendertarget
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// * Set Default Shader in Graphics Pipeline 
	GraphicsEngine::get()->setShaders();
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);

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
	GraphicsEngine::get()->release();

}