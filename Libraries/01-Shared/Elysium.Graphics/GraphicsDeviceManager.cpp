#include "GraphicsDeviceManager.hpp"

#ifndef ELYSIUM_GRAPHICS_GAME
#include "Game.hpp"
#endif

Elysium::Graphics::GraphicsDeviceManager::GraphicsDeviceManager(Game& Game)
	: _Game(Game)
{ }
Elysium::Graphics::GraphicsDeviceManager::~GraphicsDeviceManager()
{ }
