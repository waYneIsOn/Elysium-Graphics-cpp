#include "Image2DVk.hpp"

Elysium::Graphics::Rendering::Vulkan::Image2DVk::~Image2DVk()
{
	if (_NativeDepthImageViewHandle != VK_NULL_HANDLE)
	{
		vkDestroyImageView(_NativeLogicalDeviceHandle, _NativeDepthImageViewHandle, nullptr);
	}
	if (_NativeDepthImageMemoryHandle != VK_NULL_HANDLE)
	{
		vkFreeMemory(_NativeLogicalDeviceHandle, _NativeDepthImageMemoryHandle, nullptr);
	}
	if (_NativeDepthImageHandle != VK_NULL_HANDLE)
	{
		vkDestroyImage(_NativeLogicalDeviceHandle, _NativeDepthImageHandle, nullptr);
	}
}

const Elysium::Graphics::Rendering::SurfaceFormat& Elysium::Graphics::Rendering::Vulkan::Image2DVk::GetFormat() const
{
	throw 1;
}

const Elysium::Core::uint32_t& Elysium::Graphics::Rendering::Vulkan::Image2DVk::GetLevelCount() const
{
	throw 1;
}

const Elysium::Core::uint32_t& Elysium::Graphics::Rendering::Vulkan::Image2DVk::GetWidth() const
{
	throw 1;
}

const Elysium::Core::uint32_t& Elysium::Graphics::Rendering::Vulkan::Image2DVk::GetHeight() const
{
	throw 1;
}

Elysium::Graphics::Rendering::Vulkan::Image2DVk::Image2DVk(const VkDevice NativeLogicalDeviceHandle, const Elysium::Core::uint32_t Width, const Elysium::Core::uint32_t Height, const bool MipMap, const SurfaceFormat& Format)
	: _NativeLogicalDeviceHandle(NativeLogicalDeviceHandle)
{ }
