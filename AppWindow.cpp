#include "AppWindow.h"
#include <Windows.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Toolbar.h"
#include "SceneOutline.h"
#include "Inspector.h"
#include "EngineProfiler.h"


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

#pragma region Manager Initialization

	// * GameObject Initializations
	GameObjectManager::initialize();

	// * Input System Initialization
	InputSystem::initialize();
	InputSystem::getInstance()->showCursor(true);

	// * UI Initialization
	UIManager::initialize(m_hwnd);
	UINames names;
	Toolbar* menu = new Toolbar(names.MENU_SCREEN);
	SceneOutline* sceneOutline = new SceneOutline(names.HIERARCHY_SCREEN);
	Inspector* inspector = new Inspector(names.INSPECTOR_SCREEN);
	EngineProfiler* profiler = new EngineProfiler(names.PROFILER_SCREEN);

	// * Scene Camera Initialization
	SceneCameraHandler::initialize();
#pragma endregion

#pragma region Cube Initialization
#if 0

	// * Parameters of cubes
	int rot = -1; // ? rotation axis
	this->target_amt = 50; // ? Target amount of cubes to instantiate

	// * MinMax Cube Positions
	float max_x = 0.5f;
	float min_x = max_x * -1;

	float max_y = 0.5f;
	float min_y = max_y * -1;
	
	float max_z = 0.5f;
	float min_z = max_z * -1;

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	for(curr_amt; curr_amt < target_amt; curr_amt++){

		float x_pos = -1.0 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_x - min_x)));
		float y_pos = -1.0 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_y - min_y)));
		float z_pos = -1.0 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_z - min_x)));
			Cube* cube = new Cube("Cube", shader_byte_code, size_shader);
			cube->setPosition(Vector3D(x_pos, y_pos, z_pos));
			cube->setScale(Vector3D(0.1f,0.1f,0.1f));
			cube->setRotation(Vector3D(0,0,0));
	
			//switch (rand() % 3){ // ? Randomize Cube rotation
			switch (rot){ // ? Select a cube rotation
				case 0:
					cube->setRotAx('x');
					break;
				case 1:
					cube->setRotAx('y');
					break;
				case 2:
					cube->setRotAx('z');
					break;
				default:	
					cube->setRotAx('a');
			}

		cube->setSpeed(rand() % 11 + 1);
		this->object_list.push_back(cube);
	}

#endif
#pragma endregion

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

}

void AppWindow::onUpdate()
{

	Window::onUpdate();
	
	InputSystem::getInstance()->update();

	// * Clear Render Target
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, my_color[0], my_color[1], my_color[2], my_color[3]);

	// * Set Viewport of rendertarget
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(getWidth(), getHeight());

	// * Set Default Shader in Graphics Pipeline 
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);


	// for(int x = 0; x < object_list.size(); x++){
	// 	object_list[x]->update(EngineTime::getDeltaTime());
	// 	object_list[x]->draw();
	// }

	GameObjectManager::getInstance()->updateAll();
	GameObjectManager::getInstance()->renderAll(getWidth(), getHeight(), m_vs, m_ps);

	SceneCameraHandler::getInstance()->update();

	UIManager::getInstance()->drawAllUI();
	
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
	

	InputSystem::destroy();
	UIManager::destroy();
	SceneCameraHandler::destroy();
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

