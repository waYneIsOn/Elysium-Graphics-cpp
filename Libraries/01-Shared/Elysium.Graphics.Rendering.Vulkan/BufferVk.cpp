#include "BufferVk.hpp"

Elysium::Graphics::Rendering::Vulkan::BufferVk::~BufferVk()
{
	if (_NativeBufferHandle != VK_NULL_HANDLE)
	{
		vkDestroyBuffer(_NativeLogicalDeviceHandle, _NativeBufferHandle, nullptr);
	}
}

Elysium::Graphics::Rendering::Vulkan::BufferVk::BufferVk(const VkDevice NativeLogicalDeviceHandle, const VkBuffer NativeBufferHandle)
	: _NativeLogicalDeviceHandle(NativeLogicalDeviceHandle), _NativeBufferHandle(NativeBufferHandle)
{ }
