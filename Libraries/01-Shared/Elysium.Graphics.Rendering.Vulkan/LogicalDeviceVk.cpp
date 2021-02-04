#include "LogicalDeviceVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::~LogicalDeviceVk()
{
	if (_NativeLogicalDeviceHandle != VK_NULL_HANDLE)
	{
		vkDestroyDevice(_NativeLogicalDeviceHandle, nullptr);
	}
}

Elysium::Graphics::Rendering::Vulkan::QueueVk& Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::RetrieveQueue(const Elysium::Core::uint32_t FamilyIndex, const Elysium::Core::uint32_t Index)
{
	for (size_t i = 0; i < _Queues.GetLength(); i++)
	{
		if (_Queues[i]._FamilyIndex == FamilyIndex && _Queues[i]._Index == Index)
		{
			return _Queues[i];
		}
	}

	// ToDo: throw specific exception (InvalidDataException?)
	throw 1;
}

Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::LogicalDeviceVk(const VkDevice NativeLogicalDeviceHandle, Elysium::Core::Collections::Template::Array<QueueVk>&& NativeQueues)
	: _NativeLogicalDeviceHandle(NativeLogicalDeviceHandle), _Queues(std::move(NativeQueues))
{ }
