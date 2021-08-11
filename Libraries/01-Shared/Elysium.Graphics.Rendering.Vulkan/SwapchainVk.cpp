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

Elysium::Graphics::Rendering::Vulkan::SwapchainVk::SwapchainVk(const LogicalDeviceVk& LogicalDevice, SurfaceVk& Surface, PresentationParametersVk& PresentationParameters)
	: _LogicalDevice(LogicalDevice), _Surface(Surface), _PresentationParameters(PresentationParameters), _NativeSwapchainHandle(VK_NULL_HANDLE),
	_CurrentBackBufferImageIndex(0), _BackBufferImages(0), _BackBufferImageViews(0)
{
	RecreateSwapchain(VK_NULL_HANDLE);
	_Surface.SizeChanged += Elysium::Core::Delegate<void, const Elysium::Graphics::Rendering::Vulkan::SurfaceVk&>::Bind<Elysium::Graphics::Rendering::Vulkan::SwapchainVk, &Elysium::Graphics::Rendering::Vulkan::SwapchainVk::Surface_OnSizeChanged>(*this);
}
Elysium::Graphics::Rendering::Vulkan::SwapchainVk::~SwapchainVk()
{
	_Surface.SizeChanged -= Elysium::Core::Delegate<void, const Elysium::Graphics::Rendering::Vulkan::SurfaceVk&>::Bind<Elysium::Graphics::Rendering::Vulkan::SwapchainVk, &Elysium::Graphics::Rendering::Vulkan::SwapchainVk::Surface_OnSizeChanged>(*this);

	for (size_t i = 0; i < _BackBufferImageViews.GetLength(); i++)
	{
		vkDestroyImageView(_LogicalDevice._NativeLogicalDeviceHandle, _BackBufferImageViews[i], nullptr);
	}
	if (_NativeSwapchainHandle != VK_NULL_HANDLE)
	{
		vkDestroySwapchainKHR(_LogicalDevice._NativeLogicalDeviceHandle, _NativeSwapchainHandle, nullptr);
		_NativeSwapchainHandle = VK_NULL_HANDLE;
	}
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::SwapchainVk::GetBackBufferImageCount() const
{
	return _BackBufferImages.GetLength();
}

void Elysium::Graphics::Rendering::Vulkan::SwapchainVk::AquireNextImage(const Native::INativeSemaphore& PresentSemaphore, const Elysium::Core::uint64_t Timeout)
{
	const SemaphoreVk& VkPresentSemaphore = dynamic_cast<const SemaphoreVk&>(PresentSemaphore);

	VkResult Result;
	if ((Result = vkAcquireNextImageKHR(_LogicalDevice._NativeLogicalDeviceHandle, _NativeSwapchainHandle, Timeout,
		VkPresentSemaphore._NativeSemaphoreHandle, nullptr, &_CurrentBackBufferImageIndex)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}

void Elysium::Graphics::Rendering::Vulkan::SwapchainVk::PresentFrame(const Native::INativeSemaphore& RenderSemaphore, const Native::INativeQueue& PresentationQueue)
{
	const SemaphoreVk& VkRenderSemaphore = dynamic_cast<const SemaphoreVk&>(RenderSemaphore);
	const QueueVk& VkQueue = dynamic_cast<const QueueVk&>(PresentationQueue);

	VkPresentInfoKHR PresentInfo = VkPresentInfoKHR();
	PresentInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	PresentInfo.pNext = nullptr;
	PresentInfo.pImageIndices = &_CurrentBackBufferImageIndex;
	PresentInfo.pResults = nullptr;
	PresentInfo.pSwapchains = &_NativeSwapchainHandle;
	PresentInfo.swapchainCount = 1;
	PresentInfo.pWaitSemaphores = &VkRenderSemaphore._NativeSemaphoreHandle;
	PresentInfo.waitSemaphoreCount = 1;

	VkResult Result;
	if ((Result = vkQueuePresentKHR(VkQueue._NativeQueueHandle, &PresentInfo)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	_CurrentBackBufferImageIndex = (_CurrentBackBufferImageIndex + 1) % _BackBufferImages.GetLength();
}

void Elysium::Graphics::Rendering::Vulkan::SwapchainVk::RecreateSwapchain(VkSwapchainKHR PreviousNativeSwapchainHandle)
{
	// wait for any pending queues on the device
	_LogicalDevice.Wait();

	// destroy image views

	// recreate swapchain
	const VkExtent2D& Extent = (const VkExtent2D&)_PresentationParameters.GetExtent();
	
	VkSwapchainCreateInfoKHR CreateInfo = VkSwapchainCreateInfoKHR();
	CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	CreateInfo.pNext = nullptr;
	CreateInfo.flags = 0;
	CreateInfo.surface = _Surface._NativeSurfaceHandle;
	CreateInfo.minImageCount = _PresentationParameters.GetBackBufferCount();
	CreateInfo.imageFormat = (VkFormat&)_PresentationParameters.GetSurfaceFormat().Format;
	CreateInfo.imageColorSpace = (VkColorSpaceKHR&)_PresentationParameters.GetSurfaceFormat().ColorSpace;
	CreateInfo.imageExtent = Extent;
	CreateInfo.imageArrayLayers = _PresentationParameters.GetImageArrayLayers();
	CreateInfo.imageUsage = VkImageUsageFlagBits::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	CreateInfo.preTransform = (VkSurfaceTransformFlagBitsKHR)_PresentationParameters.GetTransform();
	CreateInfo.compositeAlpha = VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	CreateInfo.presentMode = (VkPresentModeKHR)_PresentationParameters.GetPresentMode();
	CreateInfo.clipped = VK_TRUE;
	CreateInfo.oldSwapchain = PreviousNativeSwapchainHandle;
	if (_LogicalDevice.GetGraphicsQueueFamilyIndex() != _LogicalDevice.GetPresentationQueueFamilyIndex())
	{
		Elysium::Core::uint32_t QueueFamilyIndices[] = { _LogicalDevice.GetGraphicsQueueFamilyIndex(), _LogicalDevice.GetPresentationQueueFamilyIndex() };

		CreateInfo.imageSharingMode = VkSharingMode::VK_SHARING_MODE_CONCURRENT;
		CreateInfo.queueFamilyIndexCount = 2;
		CreateInfo.pQueueFamilyIndices = QueueFamilyIndices;
	}
	else
	{
		CreateInfo.imageSharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
		CreateInfo.queueFamilyIndexCount = 0; // Optional
		CreateInfo.pQueueFamilyIndices = nullptr; // Optional
	}

	VkResult Result;
	if ((Result = vkCreateSwapchainKHR(_LogicalDevice._NativeLogicalDeviceHandle, &CreateInfo, nullptr, &_NativeSwapchainHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
	
	// destroy previous swapchain
	if (PreviousNativeSwapchainHandle != VK_NULL_HANDLE)
	{
		vkDestroySwapchainKHR(_LogicalDevice._NativeLogicalDeviceHandle, PreviousNativeSwapchainHandle, nullptr);
	}
	
	// recreate images
	Elysium::Core::uint32_t BackBufferImageCount = 0;
	if ((Result = vkGetSwapchainImagesKHR(_LogicalDevice._NativeLogicalDeviceHandle, _NativeSwapchainHandle, &BackBufferImageCount, nullptr)) != VK_SUCCESS)
	{
		vkDestroySwapchainKHR(_LogicalDevice._NativeLogicalDeviceHandle, _NativeSwapchainHandle, nullptr);

		throw ExceptionVk(Result);
	}
	if (BackBufferImageCount == 0)
	{
		vkDestroySwapchainKHR(_LogicalDevice._NativeLogicalDeviceHandle, _NativeSwapchainHandle, nullptr);

		// ToDo: throw specific exception
		throw 1;
	}

	_BackBufferImages = Elysium::Core::Collections::Template::Array<VkImage>(BackBufferImageCount);
	if ((Result = vkGetSwapchainImagesKHR(_LogicalDevice._NativeLogicalDeviceHandle, _NativeSwapchainHandle, &BackBufferImageCount, &_BackBufferImages[0])) != VK_SUCCESS)
	{
		vkDestroySwapchainKHR(_LogicalDevice._NativeLogicalDeviceHandle, _NativeSwapchainHandle, nullptr);

		throw ExceptionVk(Result);
	}

	// ...
	_BackBufferImageViews = Elysium::Core::Collections::Template::Array<VkImageView>(BackBufferImageCount);
	for (size_t i = 0; i < BackBufferImageCount; i++)
	{
		VkImageViewCreateInfo ImageViewCreateInfo = VkImageViewCreateInfo();
		ImageViewCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
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

		if ((Result = vkCreateImageView(_LogicalDevice._NativeLogicalDeviceHandle, &ImageViewCreateInfo, nullptr, &_BackBufferImageViews[i])) != VK_SUCCESS)
		{
			for (size_t j = 0; j < i - 1; j++)
			{
				vkDestroyImageView(_LogicalDevice._NativeLogicalDeviceHandle, _BackBufferImageViews[j], nullptr);
			}
			vkDestroySwapchainKHR(_LogicalDevice._NativeLogicalDeviceHandle, _NativeSwapchainHandle, nullptr);

			throw ExceptionVk(Result);
		}
	}

	_CurrentBackBufferImageIndex = 0;
}

void Elysium::Graphics::Rendering::Vulkan::SwapchainVk::Surface_OnSizeChanged(const Elysium::Graphics::Rendering::Vulkan::SurfaceVk& Sender)
{
	RecreateSwapchain(_NativeSwapchainHandle);
}
