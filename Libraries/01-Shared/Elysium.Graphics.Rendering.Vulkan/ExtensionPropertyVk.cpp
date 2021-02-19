#include "ExtensionPropertyVk.hpp"

Elysium::Graphics::Rendering::Vulkan::ExtensionPropertyVk::ExtensionPropertyVk()
	: _NativeProperty()
{ }
Elysium::Graphics::Rendering::Vulkan::ExtensionPropertyVk::~ExtensionPropertyVk()
{ }

const Elysium::Core::StringView Elysium::Graphics::Rendering::Vulkan::ExtensionPropertyVk::GetName() const
{
	return Core::StringView((char8_t*)_NativeProperty.extensionName);
}

const Elysium::Core::uint32_t& Elysium::Graphics::Rendering::Vulkan::ExtensionPropertyVk::GetSpecVersion() const
{
	return _NativeProperty.specVersion;
}
