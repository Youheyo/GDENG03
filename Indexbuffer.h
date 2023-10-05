#pragma once
#pragma comment (lib, "d3d11.lib")
#include <d3d11.h>
#include "GraphicsEngine.h"

class DeviceContext;

class IndexBuffer{

public:

	IndexBuffer();
	~IndexBuffer();

	bool load(void* list_vertices, UINT size_list);
	
	UINT getSizeIndexList();
	
	bool release();

private:
	UINT m_size_list;
	
	ID3D11Buffer* m_buffer;

	friend class DeviceContext;

};