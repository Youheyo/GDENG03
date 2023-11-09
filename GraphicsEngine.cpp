#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include "TextureManager.h"


GraphicsEngine::GraphicsEngine()
{


}

bool GraphicsEngine::init()
{
	m_render_system = new RenderSystem();
	m_render_system->init();

	m_tex_manager = new TextureManager();

	return true;
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return m_render_system;
}

TextureManager* GraphicsEngine::getTextureManager()
{
	return m_tex_manager;
}

bool GraphicsEngine::release()
{
	delete m_tex_manager;
	m_render_system->release();
	delete m_render_system;
	return true;
}

GraphicsEngine::~GraphicsEngine()
{

}

GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine engine;
	return &engine;
}