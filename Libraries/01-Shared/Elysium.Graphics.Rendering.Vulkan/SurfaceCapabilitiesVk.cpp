#include "SurfaceCapabilitiesVk.hpp"

Elysium::Graphics::Rendering::Vulkan::SurfaceCapabilitiesVk::~SurfaceCapabilitiesVk()
{ }

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::SurfaceCapabilitiesVk::GetMinImageCount() const
{
	return _NativeSurfaceCapabilities.minImageCount;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::SurfaceCapabilitiesVk::GetMaxImageCount() const
{
	return _NativeSurfaceCapabilities.maxImageCount;
}

const Elysium::Graphics::Rendering::Vulkan::Extent2DVk Elysium::Graphics::Rendering::Vulkan::SurfaceCapabilitiesVk::GetCurrentExtent() const
{
	return Elysium::Graphics::Rendering::Vulkan::Extent2DVk(_NativeSurfaceCapabilities.currentExtent.width, _NativeSurfaceCapabilities.currentExtent.height);
}

const Elysium::Graphics::Rendering::Vulkan::Extent2DVk Elysium::Graphics::Rendering::Vulkan::SurfaceCapabilitiesVk::GetMinImageExtent() const
{
	return Elysium::Graphics::Rendering::Vulkan::Extent2DVk(_NativeSurfaceCapabilities.minImageExtent.width, _NativeSurfaceCapabilities.minImageExtent.height);
}

const Elysium::Graphics::Rendering::Vulkan::Extent2DVk Elysium::Graphics::Rendering::Vulkan::SurfaceCapabilitiesVk::GetMaxImageExtent() const
{
	return Elysium::Graphics::Rendering::Vulkan::Extent2DVk(_NativeSurfaceCapabilities.maxImageExtent.width, _NativeSurfaceCapabilities.maxImageExtent.height);
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::SurfaceCapabilitiesVk::GetMaxImageArrayLayers() const
{
	return _NativeSurfaceCapabilities.maxImageArrayLayers;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::SurfaceCapabilitiesVk::GetSupportedTransforms() const
{
	return _NativeSurfaceCapabilities.supportedTransforms;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::SurfaceCapabilitiesVk::GetCurrentTransform() const
{
	return _NativeSurfaceCapabilities.currentTransform;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::SurfaceCapabilitiesVk::GetSupportedCompositeAlpha() const
{
	return _NativeSurfaceCapabilities.supportedCompositeAlpha;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::SurfaceCapabilitiesVk::GetSupportedUsageFlags() const
{
	return _NativeSurfaceCapabilities.supportedUsageFlags;
}

Elysium::Graphics::Rendering::Vulkan::SurfaceCapabilitiesVk::SurfaceCapabilitiesVk(const VkSurfaceCapabilitiesKHR NativeSurfaceCapabilities)
	: _NativeSurfaceCapabilities(NativeSurfaceCapabilities)
{ }
