#include "ContentManager.hpp"

Elysium::Graphics::Content::ContentManager::ContentManager(const Elysium::Graphics::Rendering::INativeGraphicsDevice& GraphicsDevice, const Elysium::Core::String& RootDirectory) noexcept
	: _GraphicsDevice(GraphicsDevice), _RootDirectory(RootDirectory)
{ }
Elysium::Graphics::Content::ContentManager::~ContentManager() noexcept
{ }
