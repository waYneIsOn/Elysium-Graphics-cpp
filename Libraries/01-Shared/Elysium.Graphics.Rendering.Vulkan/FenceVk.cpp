#include "FenceVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::FenceVk::~FenceVk()
{
	if (_NativeFenceHandle != VK_NULL_HANDLE)
	{
		vkDestroyFence(_NativeLogicalDeviceHandle, _NativeFenceHandle, nullptr);
	}
}

void Elysium::Graphics::Rendering::Vulkan::FenceVk::Wait(const Elysium::Core::uint64_t Timeout)
{
	VkResult Result;
	if ((Result = vkWaitForFences(_NativeLogicalDeviceHandle, 1, &_NativeFenceHandle, true, Timeout)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}

void Elysium::Graphics::Rendering::Vulkan::FenceVk::Reset()
{
	VkResult Result;
	if ((Result = vkResetFences(_NativeLogicalDeviceHandle, 1, &_NativeFenceHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}

Elysium::Graphics::Rendering::Vulkan::FenceVk::FenceVk(const VkDevice NativeLogicalDeviceHandle, const VkFence NativeFenceHandle)
	: _NativeLogicalDeviceHandle(NativeLogicalDeviceHandle), _NativeFenceHandle(NativeFenceHandle)
{ }
