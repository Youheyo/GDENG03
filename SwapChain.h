#pragma once
#include "GraphicsEngine.h"

class DeviceContext;

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	bool init(HWND hwnd, UINT width, UINT height);

	bool present(bool vsync);

	bool release();


private:
	IDXGISwapChain* m_swap_chain;

	ID3D11RenderTargetView* m_rtv;

	friend class DeviceContext;

};

