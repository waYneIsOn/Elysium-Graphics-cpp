#include "FenceVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSDEVICEVK
#include "GraphicsDeviceVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::FenceVk::FenceVk(const GraphicsDeviceVk& GraphicsDevice, const bool SetSignaled)
	: _GraphicsDevice(GraphicsDevice), _NativeFenceHandle(CreateNativeFence(SetSignaled))
{ }
Elysium::Graphics::Rendering::Vulkan::FenceVk::~FenceVk()
{
	DestroyNativeFence();
}

void Elysium::Graphics::Rendering::Vulkan::FenceVk::Wait(const Elysium::Core::uint64_t Timeout) const
{
	VkResult Result;
	if ((Result = vkWaitForFences(_GraphicsDevice._NativeLogicalDeviceHandle, 1, &_NativeFenceHandle, true, Timeout)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}

void Elysium::Graphics::Rendering::Vulkan::FenceVk::Reset()
{
	VkResult Result;
	if ((Result = vkResetFences(_GraphicsDevice._NativeLogicalDeviceHandle, 1, &_NativeFenceHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}

VkFence Elysium::Graphics::Rendering::Vulkan::FenceVk::CreateNativeFence(const bool SetSignaled)
{
	VkFenceCreateInfo CreateInfo = VkFenceCreateInfo();
	CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	CreateInfo.pNext = nullptr;
	CreateInfo.flags = SetSignaled == true ? VkFenceCreateFlagBits::VK_FENCE_CREATE_SIGNALED_BIT : 0;

	VkFence Fence;
	VkResult Result;
	if ((Result = vkCreateFence(_GraphicsDevice._NativeLogicalDeviceHandle, &CreateInfo, nullptr, &Fence)) != VK_NULL_HANDLE)
	{
		throw ExceptionVk(Result);
	}

	return Fence;
}

void Elysium::Graphics::Rendering::Vulkan::FenceVk::DestroyNativeFence()
{
	if (_NativeFenceHandle != VK_NULL_HANDLE)
	{
		vkDestroyFence(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeFenceHandle, nullptr);
		_NativeFenceHandle = VK_NULL_HANDLE;
	}
}
