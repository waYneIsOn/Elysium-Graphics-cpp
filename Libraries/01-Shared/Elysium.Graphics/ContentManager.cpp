#include "ContentManager.hpp"

Elysium::Graphics::Content::ContentManager::ContentManager(const Elysium::Graphics::Rendering::GraphicsDevice& GraphicsDevice, const Elysium::Core::Utf8String& RootDirectory) noexcept
	: _GraphicsDevice(GraphicsDevice), _RootDirectory(RootDirectory)
{ }

Elysium::Graphics::Content::ContentManager::~ContentManager() noexcept
{
	Unload();
}

const Elysium::Graphics::Rendering::GraphicsDevice& Elysium::Graphics::Content::ContentManager::GetGraphicsDevice() const
{
	return _GraphicsDevice;
}

void Elysium::Graphics::Content::ContentManager::Unload()
{
}
