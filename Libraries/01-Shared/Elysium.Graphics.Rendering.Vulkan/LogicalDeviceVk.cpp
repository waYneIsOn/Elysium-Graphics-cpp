#include "LogicalDeviceVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::~LogicalDeviceVk()
{
	if (_NativeLogicalDeviceHandle != VK_NULL_HANDLE)
	{
		vkDestroyDevice(_NativeLogicalDeviceHandle, nullptr);
	}
}

Elysium::Graphics::Rendering::Vulkan::SwapchainVk Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::CreateSwapchain(const SurfaceVk& Surface, const SwapchainCreateInfoVk& SwapchainCreateInfo)
{
	VkSwapchainCreateInfoKHR CreateInfo = VkSwapchainCreateInfoKHR();
	CreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	CreateInfo.pNext = nullptr;
	CreateInfo.flags = 0;
	CreateInfo.surface = Surface._NativeSurfaceHandle;
	CreateInfo.minImageCount = SwapchainCreateInfo.NumberOfImages;
	CreateInfo.imageFormat = (VkFormat&)SwapchainCreateInfo.SurfaceFormat.Format;
	CreateInfo.imageColorSpace = (VkColorSpaceKHR&)SwapchainCreateInfo.SurfaceFormat.ColorSpace;
	CreateInfo.imageExtent = (VkExtent2D&)SwapchainCreateInfo.Extend;
	CreateInfo.imageArrayLayers = SwapchainCreateInfo.ImageArrayLayers;
	CreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	CreateInfo.preTransform = (VkSurfaceTransformFlagBitsKHR&)SwapchainCreateInfo.Transform;
	CreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	CreateInfo.presentMode = (VkPresentModeKHR)SwapchainCreateInfo.PresentMode;
	CreateInfo.clipped = VK_TRUE;
	CreateInfo.oldSwapchain = VK_NULL_HANDLE;
	if (SwapchainCreateInfo.GraphicsFamilyIndex != SwapchainCreateInfo.PresentFamilyIndex)
	{
		Elysium::Core::uint32_t QueueFamilyIndices[] = { SwapchainCreateInfo.GraphicsFamilyIndex, SwapchainCreateInfo.PresentFamilyIndex };

		CreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		CreateInfo.queueFamilyIndexCount = 2;
		CreateInfo.pQueueFamilyIndices = QueueFamilyIndices;
	}
	else
	{
		CreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		CreateInfo.queueFamilyIndexCount = 0; // Optional
		CreateInfo.pQueueFamilyIndices = nullptr; // Optional
	}

	VkSwapchainKHR NativeSwapchain;
	VkResult Result;
	if ((Result = vkCreateSwapchainKHR(_NativeLogicalDeviceHandle, &CreateInfo, nullptr, &NativeSwapchain)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	Elysium::Core::uint32_t BackBufferImageCount;
	if ((Result = vkGetSwapchainImagesKHR(_NativeLogicalDeviceHandle, NativeSwapchain, &BackBufferImageCount, nullptr)) != VK_SUCCESS)
	{
		vkDestroySwapchainKHR(_NativeLogicalDeviceHandle, NativeSwapchain, nullptr);

		throw ExceptionVk(Result);
	}
	
	Elysium::Core::Collections::Template::Array<VkImage> BackBufferImages =
		Elysium::Core::Collections::Template::Array<VkImage>(BackBufferImageCount);
	if ((Result = vkGetSwapchainImagesKHR(_NativeLogicalDeviceHandle, NativeSwapchain, &BackBufferImageCount, &BackBufferImages[0])) != VK_SUCCESS)
	{
		vkDestroySwapchainKHR(_NativeLogicalDeviceHandle, NativeSwapchain, nullptr);

		throw ExceptionVk(Result);
	}

	Elysium::Core::Collections::Template::Array<VkImageView> _BackBufferImageViews =
		Elysium::Core::Collections::Template::Array<VkImageView>(BackBufferImageCount);
	for (size_t i = 0; i < BackBufferImageCount; i++)
	{
		VkImageViewCreateInfo ImageViewCreateInfo = VkImageViewCreateInfo();
		ImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		ImageViewCreateInfo.pNext = nullptr;
		ImageViewCreateInfo.flags = 0;
		ImageViewCreateInfo.image = BackBufferImages[i];
		ImageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		ImageViewCreateInfo.format = CreateInfo.imageFormat;
		ImageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		ImageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		ImageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		ImageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		ImageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		ImageViewCreateInfo.subresourceRange.baseMipLevel = 0;
		ImageViewCreateInfo.subresourceRange.levelCount = 1;
		ImageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
		ImageViewCreateInfo.subresourceRange.layerCount = 1;

		if ((Result = vkCreateImageView(_NativeLogicalDeviceHandle, &ImageViewCreateInfo, nullptr, &_BackBufferImageViews[0])) != VK_SUCCESS)
		{
			for (size_t j = 0; j < i; j++)
			{
				vkDestroyImageView(_NativeLogicalDeviceHandle, _BackBufferImageViews[j], nullptr);
			}
			vkDestroySwapchainKHR(_NativeLogicalDeviceHandle, NativeSwapchain, nullptr);

			throw ExceptionVk(Result);
		}
	}

	return SwapchainVk(_NativeLogicalDeviceHandle, NativeSwapchain, BackBufferImages, _BackBufferImageViews);
}

Elysium::Graphics::Rendering::Vulkan::QueueVk& Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::RetrieveQueue(const Elysium::Core::uint32_t FamilyIndex, const Elysium::Core::uint32_t Index)
{
	for (size_t i = 0; i < _Queues.GetLength(); i++)
	{
		if (_Queues[i]._FamilyIndex == FamilyIndex && _Queues[i]._Index == Index)
		{
			return _Queues[i];
		}
	}

	// ToDo: throw specific exception (InvalidDataException?)
	throw 1;
}

Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::LogicalDeviceVk(const VkDevice NativeLogicalDeviceHandle, Elysium::Core::Collections::Template::Array<QueueVk>&& Queues)
	: _NativeLogicalDeviceHandle(NativeLogicalDeviceHandle), _Queues(std::move(Queues))
{ }
