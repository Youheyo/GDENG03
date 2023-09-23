#include "VertexShader.h"
#include <iostream>

VertexShader::VertexShader()
{
}

VertexShader::~VertexShader()
{
}

void VertexShader::release()
{
	m_vs->Release();
	delete this;
}

bool VertexShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	if (!SUCCEEDED(GraphicsEngine::get()->m_d3d_device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs))) {
		return false;
	}
	std::cout << "Vertex Shader initialization success!";
	return true;
}