#include "GraphicsDeviceManager.hpp"

#ifndef ELYSIUM_GRAPHICS_GAME
#include "Game.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSDEVICE
#include "INativeGraphicsDevice.hpp"
#endif

Elysium::Graphics::GraphicsDeviceManager::GraphicsDeviceManager(const Game& Game, Rendering::GraphicsDevice& GraphicsDevice)
	: _Game(Game), _GraphicsDevice(GraphicsDevice)
{ }
Elysium::Graphics::GraphicsDeviceManager::~GraphicsDeviceManager()
{ }

Elysium::Graphics::Rendering::GraphicsDevice& Elysium::Graphics::GraphicsDeviceManager::GetGraphicsDevice()
{
	return _GraphicsDevice;
}

void Elysium::Graphics::GraphicsDeviceManager::ApplyChanges()
{
	// ToDo:
	//_GraphicsDevice.RecreateResources();
}

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
