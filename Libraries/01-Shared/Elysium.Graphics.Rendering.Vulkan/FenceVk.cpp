#include "FenceVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::FenceVk::FenceVk(const LogicalDeviceVk& LogicalDevice, const bool SetSignaled)
	: _LogicalDevice(LogicalDevice), _NativeFenceHandle(VK_NULL_HANDLE)
{
	VkFenceCreateInfo CreateInfo = VkFenceCreateInfo();
	CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	CreateInfo.pNext = nullptr;
	CreateInfo.flags = SetSignaled == true ? VkFenceCreateFlagBits::VK_FENCE_CREATE_SIGNALED_BIT : 0;

	VkResult Result;
	if ((Result = vkCreateFence(_LogicalDevice._NativeLogicalDeviceHandle, &CreateInfo, nullptr, &_NativeFenceHandle)) != VK_NULL_HANDLE)
	{
		throw ExceptionVk(Result);
	}
}
Elysium::Graphics::Rendering::Vulkan::FenceVk::~FenceVk()
{
	if (_NativeFenceHandle != VK_NULL_HANDLE)
	{
		vkDestroyFence(_LogicalDevice._NativeLogicalDeviceHandle, _NativeFenceHandle, nullptr);
		_NativeFenceHandle = VK_NULL_HANDLE;
	}
}

void Elysium::Graphics::Rendering::Vulkan::FenceVk::Wait(const Elysium::Core::uint64_t Timeout) const
{
	VkResult Result;
	if ((Result = vkWaitForFences(_LogicalDevice._NativeLogicalDeviceHandle, 1, &_NativeFenceHandle, true, Timeout)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}

void Elysium::Graphics::Rendering::Vulkan::FenceVk::Reset()
{
	VkResult Result;
	if ((Result = vkResetFences(_LogicalDevice._NativeLogicalDeviceHandle, 1, &_NativeFenceHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}
