#include "LayerPropertyVk.hpp"

Elysium::Graphics::Rendering::Vulkan::LayerPropertyVk::LayerPropertyVk()
	: _NativeProperty()
{ }

Elysium::Graphics::Rendering::Vulkan::LayerPropertyVk::~LayerPropertyVk()
{ }

const Elysium::Core::Utf8StringView Elysium::Graphics::Rendering::Vulkan::LayerPropertyVk::GetName() const
{
	return Elysium::Core::Utf8StringView((char8_t*)_NativeProperty.layerName);
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::LayerPropertyVk::GetSpecVersion() const
{
	return _NativeProperty.specVersion;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::LayerPropertyVk::GetImplementationVersion() const
{
	return _NativeProperty.implementationVersion;
}

const Elysium::Core::Utf8StringView Elysium::Graphics::Rendering::Vulkan::LayerPropertyVk::GetDescription() const
{
	return Elysium::Core::Utf8StringView((char8_t*)_NativeProperty.description);
}
