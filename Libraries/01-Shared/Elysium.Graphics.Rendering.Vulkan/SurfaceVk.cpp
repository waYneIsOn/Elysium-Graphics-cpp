#include "SurfaceVk.hpp"

Elysium::Graphics::Rendering::Vulkan::SurfaceVk::~SurfaceVk()
{
	if (_NativeSurfaceHandle != VK_NULL_HANDLE)
	{
		vkDestroySurfaceKHR(_NativeInstanceHandle, _NativeSurfaceHandle, nullptr);
	}
}

Elysium::Graphics::Rendering::Vulkan::SurfaceVk::SurfaceVk(const VkInstance NativeInstanceHandle, const VkSurfaceKHR NativeSurfaceHandle)
	: _NativeInstanceHandle(NativeInstanceHandle), _NativeSurfaceHandle(NativeSurfaceHandle)
{ }
