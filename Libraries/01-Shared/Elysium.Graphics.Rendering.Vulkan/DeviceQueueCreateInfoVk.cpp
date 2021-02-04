#include "DeviceQueueCreateInfoVk.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::DeviceQueueCreateInfoVk()
	: Priority(1.0f), FamilyIndex(-1), Count(-1), Capabilities(Elysium::Graphics::Rendering::Vulkan::QueueCapabilitiesVk::None)
{ }
Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::DeviceQueueCreateInfoVk(Elysium::Core::uint32_t FamilyIndex, Elysium::Core::uint32_t Count, float Priority, Elysium::Graphics::Rendering::Vulkan::QueueCapabilitiesVk Capabilities)
	: Priority(Priority), FamilyIndex(FamilyIndex), Count(Count), Capabilities(Capabilities)
{ }
Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::DeviceQueueCreateInfoVk(const DeviceQueueCreateInfoVk & Source)
	: Priority(Source.Priority), FamilyIndex(Source.FamilyIndex), Count(Source.Count), Capabilities(Source.Capabilities)
{ }
Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::DeviceQueueCreateInfoVk(DeviceQueueCreateInfoVk&& Right) noexcept
	: Priority(1.0f), FamilyIndex(-1), Count(-1), Capabilities(Elysium::Graphics::Rendering::Vulkan::QueueCapabilitiesVk::None)
{
	*this = std::move(Right);
}
Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::~DeviceQueueCreateInfoVk()
{ }

Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk& Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::operator=(const DeviceQueueCreateInfoVk & Source)
{
	if (this != &Source)
	{
		Priority = Source.Priority;
		FamilyIndex = Source.FamilyIndex;
		Count = Source.Count;
		Capabilities = Source.Capabilities;
	}
	return *this;
}

Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk& Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::operator=(DeviceQueueCreateInfoVk&& Right) noexcept
{
	if (this != &Right)
	{
		Priority = Right.Priority;
		FamilyIndex = Right.FamilyIndex;
		Count = Right.Count;
		Capabilities = Right.Capabilities;

		Right.Priority = 1.0f;
		Right.FamilyIndex = -1;
		Right.Count = -1;
		Right.Capabilities = Elysium::Graphics::Rendering::Vulkan::QueueCapabilitiesVk::None;
	}
	return *this;
}
