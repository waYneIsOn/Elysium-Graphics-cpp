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

void Elysium::Graphics::Rendering::Vulkan::SwapchainVk::AquireNextImage(const Elysium::Core::uint64_t Timeout, const INativeSemaphore& ImageAvailableSemaphore, const INativeFence& Fence)
{
	const SemaphoreVk& VkSemaphore = dynamic_cast<const SemaphoreVk&>(ImageAvailableSemaphore);
	const FenceVk& VkFence = dynamic_cast<const FenceVk&>(Fence);

	VkResult Result;
	if ((Result = vkAcquireNextImageKHR(_NativeLogicalDeviceHandle, _NativeSwapchainHandle, Timeout, VkSemaphore._NativeSemaphoreHandle, VkFence._NativeFenceHandle, &_CurrentBackBufferImageIndex)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}

void Elysium::Graphics::Rendering::Vulkan::SwapchainVk::PresentFrame(const INativeQueue& PresentationQueue, const INativeSemaphore& WaitSemaphore)
{
	const QueueVk& VkQueue = dynamic_cast<const QueueVk&>(PresentationQueue);
	const SemaphoreVk& VkSemaphore = dynamic_cast<const SemaphoreVk&>(WaitSemaphore);

	VkPresentInfoKHR PresentInfo = VkPresentInfoKHR();
	PresentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	PresentInfo.pNext = nullptr;
	PresentInfo.pImageIndices = &_CurrentBackBufferImageIndex;
	PresentInfo.pNext = NULL;
	PresentInfo.pResults = nullptr;
	// ToDo: multiple swapchains and multiple wait semaphores - also this method should be a function of a presentation queue!
	PresentInfo.pSwapchains = &_NativeSwapchainHandle;
	PresentInfo.swapchainCount = 1;
	PresentInfo.pWaitSemaphores = &VkSemaphore._NativeSemaphoreHandle;
	PresentInfo.waitSemaphoreCount = 1;

	VkResult Result;
	if ((Result = vkQueuePresentKHR(VkQueue._NativeQueueHandle, &PresentInfo)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}

Elysium::Graphics::Rendering::Vulkan::SwapchainVk::SwapchainVk(const VkDevice NativeLogicalDeviceHandle, const VkSwapchainKHR NativeSwapchainHandle, const Elysium::Core::Collections::Template::Array<VkImage>& BackBufferImages, const Elysium::Core::Collections::Template::Array<VkImageView> BackBufferImageViews)
	: _NativeLogicalDeviceHandle(NativeLogicalDeviceHandle), _NativeSwapchainHandle(NativeSwapchainHandle), _CurrentBackBufferImageIndex(0), _BackBufferImages(BackBufferImages), _BackBufferImageViews(BackBufferImageViews)
{ }
