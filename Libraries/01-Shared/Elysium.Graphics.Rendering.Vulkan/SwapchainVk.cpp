#include "SwapchainVk.hpp"

Elysium::Graphics::Rendering::Vulkan::SwapchainVk::~SwapchainVk()
{
	for (size_t i = 0; i < _BackBufferImageViews.GetLength(); i++)
	{
		vkDestroyImageView(_NativeLogicalDeviceHandle, _BackBufferImageViews[i], nullptr);
	}

	if (_NativeSwapchainHandle != VK_NULL_HANDLE)
	{
		vkDestroySwapchainKHR(_NativeLogicalDeviceHandle, _NativeSwapchainHandle, nullptr);
	}
}

Elysium::Graphics::Rendering::Vulkan::SwapchainVk::SwapchainVk(const VkDevice NativeLogicalDeviceHandle, const VkSwapchainKHR NativeSwapchainHandle, const Elysium::Core::Collections::Template::Array<VkImage>& BackBufferImages, const Elysium::Core::Collections::Template::Array<VkImageView> BackBufferImageViews)
	: _NativeLogicalDeviceHandle(NativeLogicalDeviceHandle), _NativeSwapchainHandle(NativeSwapchainHandle), _BackBufferImages(BackBufferImages), _BackBufferImageViews(BackBufferImageViews)
{ }
