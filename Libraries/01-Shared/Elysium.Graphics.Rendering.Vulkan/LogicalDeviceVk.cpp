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

Elysium::Graphics::Rendering::Vulkan::SwapchainVk Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::CreateSwapchain(const Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk& PresentationParameter)
{
	VkSwapchainCreateInfoKHR CreateInfo = VkSwapchainCreateInfoKHR();
	CreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	CreateInfo.pNext = nullptr;
	CreateInfo.flags = 0;
	CreateInfo.surface = (VkSurfaceKHR)PresentationParameter.GetSurfaceHandle();
	CreateInfo.minImageCount = PresentationParameter.GetBackBufferCount();
	CreateInfo.imageFormat = (VkFormat&)PresentationParameter.GetSurfaceFormat().Format;
	CreateInfo.imageColorSpace = (VkColorSpaceKHR&)PresentationParameter.GetSurfaceFormat().ColorSpace;
	CreateInfo.imageExtent = (VkExtent2D&)PresentationParameter.GetExtent();
	CreateInfo.imageArrayLayers = PresentationParameter.GetImageArrayLayers();
	CreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	CreateInfo.preTransform = (VkSurfaceTransformFlagBitsKHR)PresentationParameter.GetTransform();
	CreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	CreateInfo.presentMode = (VkPresentModeKHR)PresentationParameter.GetPresentMode();
	CreateInfo.clipped = VK_TRUE;
	CreateInfo.oldSwapchain = VK_NULL_HANDLE;
	if (PresentationParameter.GetGraphicsQueueFamilyIndex() != PresentationParameter.GetPresentationQueueFamilyIndex())
	{
		Elysium::Core::uint32_t QueueFamilyIndices[] = { PresentationParameter.GetGraphicsQueueFamilyIndex(), PresentationParameter.GetPresentationQueueFamilyIndex() };

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
			for (size_t j = 0; j < i - 1; j++)
			{
				vkDestroyImageView(_NativeLogicalDeviceHandle, _BackBufferImageViews[j], nullptr);
			}
			vkDestroySwapchainKHR(_NativeLogicalDeviceHandle, NativeSwapchain, nullptr);

			throw ExceptionVk(Result);
		}
	}

	return SwapchainVk(_NativeLogicalDeviceHandle, NativeSwapchain, BackBufferImages, _BackBufferImageViews);
}

Elysium::Graphics::Rendering::Vulkan::FenceVk& Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::RetrieveFence()
{
	throw 1;
}

Elysium::Graphics::Rendering::Vulkan::SemaphoreVk& Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::RetrieveSemaphore()
{
	throw 1;
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

void Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::Wait()
{
	VkResult Result;
	if ((Result = vkDeviceWaitIdle(_NativeLogicalDeviceHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}

Elysium::Graphics::Rendering::Vulkan::FenceVk Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::CreateFenceTest()
{
	VkFenceCreateInfo CreateInfo = VkFenceCreateInfo();
	CreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	CreateInfo.pNext = nullptr;
	CreateInfo.flags = 0;

	VkResult Result;
	VkFence NativeFenceHandle;
	if ((Result = vkCreateFence(_NativeLogicalDeviceHandle, &CreateInfo, nullptr, &NativeFenceHandle)) != VK_NULL_HANDLE)
	{
		throw ExceptionVk(Result);
	}

	return FenceVk(_NativeLogicalDeviceHandle, NativeFenceHandle);
}

Elysium::Graphics::Rendering::Vulkan::SemaphoreVk Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::CreateSemaphoreTest()
{
	VkSemaphoreCreateInfo CreateInfo = VkSemaphoreCreateInfo();
	CreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	CreateInfo.pNext = nullptr;
	CreateInfo.flags = 0;

	VkResult Result;
	VkSemaphore NativeSemaphoreHandle;
	if ((Result = vkCreateSemaphore(_NativeLogicalDeviceHandle, &CreateInfo, nullptr, &NativeSemaphoreHandle)) != VK_NULL_HANDLE)
	{
		throw ExceptionVk(Result);
	}

	return SemaphoreVk(_NativeLogicalDeviceHandle, NativeSemaphoreHandle);
}

Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::LogicalDeviceVk(const VkDevice NativeLogicalDeviceHandle, Elysium::Core::Collections::Template::Array<QueueVk>&& Queues)
	: _NativeLogicalDeviceHandle(NativeLogicalDeviceHandle), _Queues(std::move(Queues))
{ }
