#include "CommandPoolVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::CommandPoolVk::CommandPoolVk(const LogicalDeviceVk& LogicalDevice, const QueueVk& Queue)
	: _LogicalDevice(LogicalDevice), _NativeCommandPoolHandle(VK_NULL_HANDLE)
{
	VkCommandPoolCreateInfo CreateInfo = VkCommandPoolCreateInfo();
	CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	CreateInfo.pNext = nullptr;
	CreateInfo.flags = 0;
	CreateInfo.queueFamilyIndex = Queue.GetFamilyIndex();

	VkResult Result;
	if ((Result = vkCreateCommandPool(_LogicalDevice._NativeLogicalDeviceHandle, &CreateInfo, nullptr, &_NativeCommandPoolHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}
Elysium::Graphics::Rendering::Vulkan::CommandPoolVk::~CommandPoolVk()
{
	if (_NativeCommandPoolHandle != VK_NULL_HANDLE)
	{
		vkDestroyCommandPool(_LogicalDevice._NativeLogicalDeviceHandle, _NativeCommandPoolHandle, nullptr);
		_NativeCommandPoolHandle = VK_NULL_HANDLE;
	}
}

void Elysium::Graphics::Rendering::Vulkan::CommandPoolVk::Reset()
{
	VkResult Result;
	if ((Result = vkResetCommandPool(_LogicalDevice._NativeLogicalDeviceHandle, _NativeCommandPoolHandle, 
		VkCommandPoolResetFlagBits::VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}
