#pragma once
#pragma comment (lib, "d3d11.lib")
#include <d3d11.h>
#include "SwapChain.h"

class SwapChain;
class VertexBuffer;

class DeviceContext

{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	~DeviceContext();

	void clearRenderTargetColor(SwapChain* swap_chain ,float red, float green, float blue, float alpha);
	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void drawTriangleList(UINT vertext_count, UINT start_vertex_index);
	void setViewportSize(UINT width, UINT height);

	bool release();

private:
	ID3D11DeviceContext* m_device_context;
};

