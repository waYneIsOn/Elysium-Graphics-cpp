#include "SwapchainVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif



#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FENCEVK
#include "FenceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_QUEUEVK
#include "QueueVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SEMAPHOREVK
#include "SemaphoreVk.hpp"
#endif



Elysium::Graphics::Rendering::Vulkan::SwapchainVk::SwapchainVk(const LogicalDeviceVk& LogicalDevice)
	: _LogicalDevice(LogicalDevice), _NativeSwapchainHandle(VK_NULL_HANDLE), _CurrentBackBufferImageIndex(0),
	_BackBufferImages(0), _BackBufferImageViews(0), _Fences(0), _ImageAvailableSemaphores(0), _RendererFinishedSemaphores(0)
{
	RecreateSwapchain(VK_NULL_HANDLE);
}
Elysium::Graphics::Rendering::Vulkan::SwapchainVk::~SwapchainVk()
{
	for (size_t i = 0; i < _BackBufferImageViews.GetLength(); i++)
	{
		vkDestroyImageView(_LogicalDevice._NativeLogicalDeviceHandle, _BackBufferImageViews[i], nullptr);
	}

	if (_NativeSwapchainHandle != VK_NULL_HANDLE)
	{
		vkDestroySwapchainKHR(_LogicalDevice._NativeLogicalDeviceHandle, _NativeSwapchainHandle, nullptr);
	}
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::SwapchainVk::GetBackBufferImageCount() const
{
	return _BackBufferImages.GetLength();
}

void Elysium::Graphics::Rendering::Vulkan::SwapchainVk::Recreate()
{
	RecreateSwapchain(_NativeSwapchainHandle);
}

void Elysium::Graphics::Rendering::Vulkan::SwapchainVk::AquireNextImage(const Elysium::Core::uint64_t Timeout)
{
	VkResult Result;
	if ((Result = vkAcquireNextImageKHR(_LogicalDevice._NativeLogicalDeviceHandle, _NativeSwapchainHandle, Timeout,
		_ImageAvailableSemaphores[_CurrentBackBufferImageIndex], nullptr, &_CurrentBackBufferImageIndex)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}

void Elysium::Graphics::Rendering::Vulkan::SwapchainVk::PresentFrame(const INativeQueue& PresentationQueue)
{
	const QueueVk& VkQueue = dynamic_cast<const QueueVk&>(PresentationQueue);

	VkPresentInfoKHR PresentInfo = VkPresentInfoKHR();
	PresentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	PresentInfo.pNext = nullptr;
	PresentInfo.pImageIndices = &_CurrentBackBufferImageIndex;
	PresentInfo.pResults = nullptr;
	// ToDo: multiple swapchains and multiple wait semaphores - also this method should be a function of a presentation queue!
	PresentInfo.pSwapchains = &_NativeSwapchainHandle;
	PresentInfo.swapchainCount = 1;
	PresentInfo.pWaitSemaphores = &_RendererFinishedSemaphores[_CurrentBackBufferImageIndex];
	PresentInfo.waitSemaphoreCount = 1;

	VkResult Result;
	if ((Result = vkQueuePresentKHR(VkQueue._NativeQueueHandle, &PresentInfo)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	_CurrentBackBufferImageIndex = (_CurrentBackBufferImageIndex + 1) % _BackBufferImages.GetLength();
	VkQueue.Wait();
	vkDeviceWaitIdle(_LogicalDevice._NativeLogicalDeviceHandle);
}

void Elysium::Graphics::Rendering::Vulkan::SwapchainVk::RecreateSwapchain(VkSwapchainKHR PreviousNativeSwapchainHandle)
{
	_LogicalDevice.Wait();

	const PresentationParametersVk& PresentationParameter = _LogicalDevice.GetPresentationParameters();

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
	CreateInfo.oldSwapchain = PreviousNativeSwapchainHandle;
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

	VkResult Result;
	if ((Result = vkCreateSwapchainKHR(_LogicalDevice._NativeLogicalDeviceHandle, &CreateInfo, nullptr, &_NativeSwapchainHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	if (PreviousNativeSwapchainHandle != VK_NULL_HANDLE)
	{
		vkDestroySwapchainKHR(_LogicalDevice._NativeLogicalDeviceHandle, PreviousNativeSwapchainHandle, nullptr);
	}

	Elysium::Core::uint32_t BackBufferImageCount;
	if ((Result = vkGetSwapchainImagesKHR(_LogicalDevice._NativeLogicalDeviceHandle, _NativeSwapchainHandle, &BackBufferImageCount, nullptr)) != VK_SUCCESS)
	{
		vkDestroySwapchainKHR(_LogicalDevice._NativeLogicalDeviceHandle, _NativeSwapchainHandle, nullptr);

		throw ExceptionVk(Result);
	}

	_CurrentBackBufferImageIndex = 0;

	_BackBufferImages = Elysium::Core::Collections::Template::Array<VkImage>(BackBufferImageCount);
	if ((Result = vkGetSwapchainImagesKHR(_LogicalDevice._NativeLogicalDeviceHandle, _NativeSwapchainHandle, &BackBufferImageCount, &_BackBufferImages[0])) != VK_SUCCESS)
	{
		vkDestroySwapchainKHR(_LogicalDevice._NativeLogicalDeviceHandle, _NativeSwapchainHandle, nullptr);

		throw ExceptionVk(Result);
	}

	_BackBufferImageViews = Elysium::Core::Collections::Template::Array<VkImageView>(BackBufferImageCount);
	for (size_t i = 0; i < BackBufferImageCount; i++)
	{
		VkImageViewCreateInfo ImageViewCreateInfo = VkImageViewCreateInfo();
		ImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		ImageViewCreateInfo.pNext = nullptr;
		ImageViewCreateInfo.flags = 0;
		ImageViewCreateInfo.image = _BackBufferImages[i];
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

		if ((Result = vkCreateImageView(_LogicalDevice._NativeLogicalDeviceHandle, &ImageViewCreateInfo, nullptr, &_BackBufferImageViews[0])) != VK_SUCCESS)
		{
			for (size_t j = 0; j < i - 1; j++)
			{
				vkDestroyImageView(_LogicalDevice._NativeLogicalDeviceHandle, _BackBufferImageViews[j], nullptr);
			}
			vkDestroySwapchainKHR(_LogicalDevice._NativeLogicalDeviceHandle, _NativeSwapchainHandle, nullptr);

			throw ExceptionVk(Result);
		}
	}

	if (BackBufferImageCount != _Fences.GetLength())
	{
		_Fences = Elysium::Core::Collections::Template::Array<VkFence>(BackBufferImageCount);
		for (size_t i = 0; i < BackBufferImageCount; i++)
		{
			VkFenceCreateInfo CreateInfo = VkFenceCreateInfo();
			CreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			CreateInfo.pNext = nullptr;
			CreateInfo.flags = 0;

			VkResult Result;
			if ((Result = vkCreateFence(_LogicalDevice._NativeLogicalDeviceHandle, &CreateInfo, nullptr, &_Fences[i])) != VK_NULL_HANDLE)
			{
				for (size_t j = 0; j < BackBufferImageCount; j++)
				{
					vkDestroyImageView(_LogicalDevice._NativeLogicalDeviceHandle, _BackBufferImageViews[j], nullptr);
				}
				for (size_t j = 0; j < i - 1; j++)
				{
					vkDestroyFence(_LogicalDevice._NativeLogicalDeviceHandle, _Fences[j], nullptr);
				}
				vkDestroySwapchainKHR(_LogicalDevice._NativeLogicalDeviceHandle, _NativeSwapchainHandle, nullptr);

				throw ExceptionVk(Result);
			}
		}

		_ImageAvailableSemaphores = Elysium::Core::Collections::Template::Array<VkSemaphore>(BackBufferImageCount);
		for (size_t i = 0; i < BackBufferImageCount; i++)
		{
			VkSemaphoreCreateInfo CreateInfo = VkSemaphoreCreateInfo();
			CreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
			CreateInfo.pNext = nullptr;
			CreateInfo.flags = 0;

			VkResult Result;
			if ((Result = vkCreateSemaphore(_LogicalDevice._NativeLogicalDeviceHandle, &CreateInfo, nullptr, &_ImageAvailableSemaphores[i])) != VK_NULL_HANDLE)
			{
				for (size_t j = 0; j < BackBufferImageCount; j++)
				{
					vkDestroyFence(_LogicalDevice._NativeLogicalDeviceHandle, _Fences[j], nullptr);
					vkDestroyImageView(_LogicalDevice._NativeLogicalDeviceHandle, _BackBufferImageViews[j], nullptr);
				}
				for (size_t j = 0; j < i - 1; j++)
				{
					vkDestroySemaphore(_LogicalDevice._NativeLogicalDeviceHandle, _ImageAvailableSemaphores[j], nullptr);
				}
				vkDestroySwapchainKHR(_LogicalDevice._NativeLogicalDeviceHandle, _NativeSwapchainHandle, nullptr);

				throw ExceptionVk(Result);
			}
		}

		_RendererFinishedSemaphores = Elysium::Core::Collections::Template::Array<VkSemaphore>(BackBufferImageCount);
		for (size_t i = 0; i < BackBufferImageCount; i++)
		{
			VkSemaphoreCreateInfo CreateInfo = VkSemaphoreCreateInfo();
			CreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
			CreateInfo.pNext = nullptr;
			CreateInfo.flags = 0;

			VkResult Result;
			if ((Result = vkCreateSemaphore(_LogicalDevice._NativeLogicalDeviceHandle, &CreateInfo, nullptr, &_RendererFinishedSemaphores[i])) != VK_NULL_HANDLE)
			{
				for (size_t j = 0; j < BackBufferImageCount; j++)
				{
					vkDestroyFence(_LogicalDevice._NativeLogicalDeviceHandle, _Fences[j], nullptr);
					vkDestroyImageView(_LogicalDevice._NativeLogicalDeviceHandle, _BackBufferImageViews[j], nullptr);
					vkDestroySemaphore(_LogicalDevice._NativeLogicalDeviceHandle, _ImageAvailableSemaphores[j], nullptr);
				}
				for (size_t j = 0; j < i - 1; j++)
				{
					vkDestroySemaphore(_LogicalDevice._NativeLogicalDeviceHandle, _RendererFinishedSemaphores[j], nullptr);
				}
				vkDestroySwapchainKHR(_LogicalDevice._NativeLogicalDeviceHandle, _NativeSwapchainHandle, nullptr);

				throw ExceptionVk(Result);
			}
		}
	}
}
