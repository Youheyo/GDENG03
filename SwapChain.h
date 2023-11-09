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

	ID3D11RenderTargetView* getRenderTargetView();
	ID3D11DepthStencilView* getDepthStencilView();
	ID3D11ShaderResourceView* getShaderResourceView();

private:
	IDXGISwapChain* m_swap_chain;

	ID3D11RenderTargetView* m_rtv;
	ID3D11DepthStencilView* m_dsv;

	ID3D11RasterizerState* rsr;

	ID3D11ShaderResourceView* srv;
	D3D11_TEXTURE2D_DESC text2d_desc;
	friend class DeviceContext;

};