#include "QueueFamilyPropertyVk.hpp"

Elysium::Graphics::Rendering::Vulkan::QueueFamilyPropertyVk::QueueFamilyPropertyVk()
{ }
Elysium::Graphics::Rendering::Vulkan::QueueFamilyPropertyVk::~QueueFamilyPropertyVk()
{ }

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::QueueFamilyPropertyVk::GetIndex() const
{
	return _Index;
}

const Elysium::Graphics::Rendering::Vulkan::QueueCapabilitiesVk Elysium::Graphics::Rendering::Vulkan::QueueFamilyPropertyVk::GetSupportedOperations() const
{
	return (Elysium::Graphics::Rendering::Vulkan::QueueCapabilitiesVk)_NativeProperties.queueFlags;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::QueueFamilyPropertyVk::GetCount() const
{
	return _NativeProperties.queueCount;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::QueueFamilyPropertyVk::GetTimestampValidBits() const
{
	return _NativeProperties.timestampValidBits;
}
