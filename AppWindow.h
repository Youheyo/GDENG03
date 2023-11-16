#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "EngineTime.h"
#include "Cube.h"
#include <vector>
#include "SceneCameraHandler.h"
#include "UIManager.h"
#include "GameObjectManager.h"
#include "RasterizerState.h"
#include "PhysicsSystem.h"

class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();


	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	
	void initializeEngine();
	void initializeUI();

	LONG getWidth();
	LONG getHeight();

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point deltaPos);

	virtual void onLeftMouseDown(const Point deltaPos);
	virtual void onLeftMouseUp(const Point deltaPos);

	virtual void onRightMouseDown(const Point deltaPos);
	virtual void onRightMouseUp(const Point deltaPos);

private:
#pragma region SwapChain, Buffers and Shaders

	SwapChain* m_swap_chain;

	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;

	RasterizerState* m_rss_wire;
	RasterizerState* m_rss_solid;

	bool wireMode = false;
#pragma endregion

	// * Cube Objects
	int target_amt = 1;
	int curr_amt = 0;
	std::vector<AGameObject*> object_list;
	bool canAnimate = true;

	bool show_demo_window = false;
	bool show_scene_settings_window = true;


	float my_color[4] = { 0.6f, 0, 0 , 1};


};