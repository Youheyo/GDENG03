#pragma once
#pragma comment (lib, "d3d11.lib")
#include <d3d11.h>
#include "SwapChain.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "Indexbuffer.h"

class SwapChain;
class VertexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class IndexBuffer;

class DeviceContext{
	
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	~DeviceContext();

	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void setIndexBuffer(IndexBuffer* index_buffer);
	
	void clearRenderTargetColor(SwapChain* swap_chain ,float red, float green, float blue, float alpha);
	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);

	void setViewportSize(UINT width, UINT height);

	void setVertexShader(VertexShader* vertex_shader);
	void setPixelShader(PixelShader* pixel_shader);

	void setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* buffer);
	void setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* buffer);

	bool release();

	ID3D11DeviceContext* getDeviceContext();

private:
	ID3D11DeviceContext* m_device_context;

	friend class ConstantBuffer;
};

