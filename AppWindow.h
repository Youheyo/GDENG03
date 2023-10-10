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

class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	void updateQuadPosition();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point deltaPos);

	virtual void onLeftMouseDown(const Point deltaPos);
	virtual void onLeftMouseUp(const Point deltaPos);

	virtual void onRightMouseDown(const Point deltaPos);
	virtual void onRightMouseUp(const Point deltaPos);

private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;

	float m_old_delta;
	float m_new_delta;
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;

};