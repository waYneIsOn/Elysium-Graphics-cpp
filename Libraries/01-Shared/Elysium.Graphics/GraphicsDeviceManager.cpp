#include "GraphicsDeviceManager.hpp"

#ifndef ELYSIUM_GRAPHICS_GAME
#include "Game.hpp"
#endif

Elysium::Graphics::GraphicsDeviceManager::~GraphicsDeviceManager()
{ }

Elysium::Graphics::GraphicsDeviceManager::GraphicsDeviceManager(Game& Game)
	: _Game(Game)
{ }

const bool Elysium::Graphics::GraphicsDeviceManager::BeginDraw()
{
	return true;
}

void Elysium::Graphics::GraphicsDeviceManager::EndDraw()
{
}
