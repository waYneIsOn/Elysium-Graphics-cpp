#include "CommandPoolVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::CommandPoolVk::CommandPoolVk(const GraphicsDeviceVk& GraphicsDevice, const LogicalDeviceVk& LogicalDevice, const QueueVk& Queue)
	: _GraphicsDevice(GraphicsDevice), _LogicalDevice(LogicalDevice), _Queue(Queue), _NativeCommandPoolHandle(CreateNativeCommandPool())
{ }
Elysium::Graphics::Rendering::Vulkan::CommandPoolVk::~CommandPoolVk()
{
	vkDestroyCommandPool(_LogicalDevice._NativeLogicalDeviceHandle, _NativeCommandPoolHandle, nullptr);
}

Elysium::Graphics::Rendering::INativeCommandBuffer* Elysium::Graphics::Rendering::Vulkan::CommandPoolVk::CreateCommandBuffer(const bool IsPrimary)
{
	return new CommandBufferVk(_GraphicsDevice, _LogicalDevice, *this, IsPrimary);
}

void Elysium::Graphics::Rendering::Vulkan::CommandPoolVk::Reset()
{
	throw 1;
	/*
	VkResult Result;
	if ((Result = vkResetCommandPool(_LogicalDevice._NativeLogicalDeviceHandle, _NativeCommandPoolHandle, 
		VkCommandPoolResetFlagBits::VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
	*/
}

const VkCommandPool Elysium::Graphics::Rendering::Vulkan::CommandPoolVk::CreateNativeCommandPool()
{
	VkCommandPoolCreateInfo CreateInfo = VkCommandPoolCreateInfo();
	CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	CreateInfo.pNext = nullptr;
	CreateInfo.flags = VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	CreateInfo.queueFamilyIndex = _Queue.GetFamilyIndex();

	VkResult Result;
	VkCommandPool NativeCommandPoolHandle;
	if ((Result = vkCreateCommandPool(_LogicalDevice._NativeLogicalDeviceHandle, &CreateInfo, nullptr, &NativeCommandPoolHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	return NativeCommandPoolHandle;
}
