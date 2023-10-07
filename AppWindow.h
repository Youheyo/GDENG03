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
#include "EngineTime.h"
#include "Cube.h"
#include <vector>

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();


	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	
	LONG getWidth();
	LONG getHeight();

private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;

	int target_amt = 2;
	int curr_amt = 0;
	std::vector<GameObject*> object_list;

};