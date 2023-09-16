#pragma once
#pragma comment (lib, "d3d11.lib")
#include <d3d11.h>
#include "SwapChain.h"

class SwapChain;

class DeviceContext

{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	~DeviceContext();

	bool clearRenderTargetColor(SwapChain* swap_chain ,float red, float green, float blue, float alpha);

	bool release();

private:
	ID3D11DeviceContext* m_device_context;
};

