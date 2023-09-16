#pragma once
#pragma comment (lib, "d3d11.lib")
#include <d3d11.h>
#include "SwapChain.h"	

class SwapChain;

class GraphicsEngine
{

public: 
	GraphicsEngine();

	bool init();

	bool release();

	~GraphicsEngine();

	SwapChain* createSwapChain();

	static GraphicsEngine* get();

private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
	ID3D11DeviceContext* m_imm_context;

	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;

	friend class SwapChain;
};

