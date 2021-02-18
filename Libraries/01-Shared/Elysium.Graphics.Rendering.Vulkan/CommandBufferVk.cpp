#include "CommandBufferVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::CommandBufferVk(const CommandPoolVk& CommandPool, const bool IsPrimary)
	: _CommandPool(CommandPool), _NativeCommandBufferHandle(VK_NULL_HANDLE)
{
	VkCommandBufferAllocateInfo  AllocateInfo = VkCommandBufferAllocateInfo();
	AllocateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	AllocateInfo.pNext = nullptr;
	AllocateInfo.commandPool = _CommandPool._NativeCommandPoolHandle;
	AllocateInfo.level = IsPrimary == true ? VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY : VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_SECONDARY;
	AllocateInfo.commandBufferCount = 1;	// ToDo: number of swapchain backbuffer/framebuffer images!!!

	VkResult Result;
	if ((Result = vkAllocateCommandBuffers(_CommandPool._LogicalDevice._NativeLogicalDeviceHandle, &AllocateInfo, &_NativeCommandBufferHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}
Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::~CommandBufferVk()
{
	// commandbuffers are implicitly cleaned up when the commandpool is destroyed so there is nothing to do here
}
