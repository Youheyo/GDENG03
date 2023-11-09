#include "SwapChain.h"
#include <iostream>

SwapChain::SwapChain()
{
}

SwapChain::~SwapChain()
{
}

bool SwapChain::init(HWND hwnd, UINT width, UINT height){

	ID3D11Device* device = GraphicsEngine::get()->m_d3d_device;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Numerator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality= 0;
	desc.Windowed = TRUE;

	//Create swap chain for window
	HRESULT hr = GraphicsEngine::get()->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

	if (FAILED(hr)) {
		return false;
	}

	ID3D11Texture2D* texture = NULL;
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&texture);

	if (FAILED(hr)) {
		return false;
	}

	device->CreateRenderTargetView(texture, NULL, &m_rtv);
	if (FAILED(hr)) {
		return false;
	}
	texture->Release();


	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	
	texture = nullptr;
	hr = device->CreateTexture2D( &descDepth, NULL, &texture);
	if(FAILED(hr)){
		return false;
	}
	
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderDesc = {};
	shaderDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	shaderDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderDesc.Texture2D.MipLevels = 1;
	shaderDesc.Texture2D.MostDetailedMip = 0;

	hr = device->CreateShaderResourceView(texture, NULL, &srv);
	if(FAILED(hr)){
		return false;
	}

	GraphicsEngine::get()->getImmediateDeviceContext()->setShaderResource(srv);

	HRESULT depthStencilHr = device->CreateDepthStencilView(texture, NULL, &this->m_dsv);
	texture->Release();

	D3D11_RASTERIZER_DESC wireframeDesc;
    ZeroMemory(&wireframeDesc, sizeof(wireframeDesc));
    wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
    wireframeDesc.CullMode = D3D11_CULL_BACK;
    wireframeDesc.FrontCounterClockwise = false;
    wireframeDesc.DepthClipEnable = true;
    device->CreateRasterizerState(&wireframeDesc, &rsr);

	return true;
}

bool SwapChain::present(bool vsync)
{
	m_swap_chain->Present(vsync, NULL);

	return true;
}

bool SwapChain::release()
{
	m_swap_chain->Release();
	delete this;
	return true;
}

ID3D11RenderTargetView *SwapChain::getRenderTargetView()
{
    return m_rtv;
}

ID3D11DepthStencilView *SwapChain::getDepthStencilView()
{
    return m_dsv;
}

ID3D11ShaderResourceView *SwapChain::getShaderResourceView()
{
	return srv;
}
