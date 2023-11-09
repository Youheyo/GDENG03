#pragma once
#include <d3d11.h>
#include "GraphicsEngine.h"
#include "DeviceContext.h"

class DeviceContext;

class RasterizerState{

public:
	RasterizerState();
	~RasterizerState();

	bool release();

	bool load(bool isWire);

private:

	ID3D11RasterizerState* m_rss;

	friend class DeviceContext;
};