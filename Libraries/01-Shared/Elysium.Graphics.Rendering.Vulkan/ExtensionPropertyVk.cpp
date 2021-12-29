#include "ExtensionPropertyVk.hpp"

Elysium::Graphics::Rendering::Vulkan::ExtensionPropertyVk::ExtensionPropertyVk()
	: _NativeProperty()
{ }

Elysium::Graphics::Rendering::Vulkan::ExtensionPropertyVk::~ExtensionPropertyVk()
{ }

const Elysium::Core::Utf8StringView Elysium::Graphics::Rendering::Vulkan::ExtensionPropertyVk::GetName() const
{
	return Elysium::Core::Utf8StringView((char8_t*)_NativeProperty.extensionName);
}

const Elysium::Core::uint32_t& Elysium::Graphics::Rendering::Vulkan::ExtensionPropertyVk::GetSpecVersion() const
{
	return _NativeProperty.specVersion;
}
