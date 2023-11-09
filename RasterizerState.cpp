#include "RasterizerState.h"


RasterizerState::RasterizerState() {
    
}

RasterizerState::~RasterizerState() {
    
}

bool RasterizerState::release() {
    this->m_rss->Release();
	delete this;
	return true;
}

bool RasterizerState::load(bool isWire) {

    D3D11_RASTERIZER_DESC wireframeDesc;
    ZeroMemory(&wireframeDesc, sizeof(wireframeDesc));
	if(isWire){
    	wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	}
	else{
		wireframeDesc.FillMode = D3D11_FILL_SOLID;
	}
    wireframeDesc.CullMode = D3D11_CULL_BACK;
    wireframeDesc.FrontCounterClockwise = false;
    wireframeDesc.DepthClipEnable = true;

    if(FAILED(GraphicsEngine::get()->getDirect3DDevice()->CreateRasterizerState(&wireframeDesc, &m_rss))){
		return false;
	}

	return true;
}
