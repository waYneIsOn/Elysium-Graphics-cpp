#include "GraphicsDeviceManager.hpp"

#ifndef ELYSIUM_GRAPHICS_GAME
#include "Game.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSDEVICE
#include "INativeGraphicsDevice.hpp"
#endif

Elysium::Graphics::GraphicsDeviceManager::~GraphicsDeviceManager()
{ }

Elysium::Graphics::Rendering::INativeGraphicsDevice& Elysium::Graphics::GraphicsDeviceManager::GetGraphicsDevice()
{
	return _GraphicsDevice;
}

Elysium::Graphics::GraphicsDeviceManager::GraphicsDeviceManager(Game& Game, Rendering::INativeGraphicsDevice& GraphicsDevice)
	: _Game(Game), _GraphicsDevice(GraphicsDevice)
{ }

void Elysium::Graphics::GraphicsDeviceManager::Wait() const
{
	_GraphicsDevice.Wait();
}

const bool Elysium::Graphics::GraphicsDeviceManager::BeginDraw()
{
	return _GraphicsDevice.BeginDraw();
}

void Elysium::Graphics::GraphicsDeviceManager::EndDraw()
{
	_GraphicsDevice.EndDraw();
}
