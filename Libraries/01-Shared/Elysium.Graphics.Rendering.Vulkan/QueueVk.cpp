#include "QueueVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Graphics::Rendering::Vulkan::QueueVk::QueueVk(const LogicalDeviceVk& LogicalDevice, const Elysium::Core::uint32_t FamilyIndex, Elysium::Core::uint32_t Index)
	: _LogicalDevice(LogicalDevice), _NativeQueueHandle(VK_NULL_HANDLE), _FamilyIndex(FamilyIndex), _Index(Index)
{
	VkDeviceQueueInfo2 DeviceQueueInfo = VkDeviceQueueInfo2();
	DeviceQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2;
	DeviceQueueInfo.pNext = nullptr;
	DeviceQueueInfo.flags = 0;
	DeviceQueueInfo.queueFamilyIndex = _FamilyIndex;
	DeviceQueueInfo.queueIndex = _Index;

	vkGetDeviceQueue2(_LogicalDevice._NativeLogicalDeviceHandle, &DeviceQueueInfo, &_NativeQueueHandle);
	//vkGetDeviceQueue(_LogicalDevice._NativeLogicalDeviceHandle, _FamilyIndex, _Index, &_NativeQueueHandle);
}
Elysium::Graphics::Rendering::Vulkan::QueueVk::~QueueVk()
{
	// queues are implicitly cleaned up when the logical device is destroyed so there is nothing to do here
}

void Elysium::Graphics::Rendering::Vulkan::QueueVk::Wait() const
{
	VkResult Result;
	if ((Result = vkQueueWaitIdle(_NativeQueueHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}
