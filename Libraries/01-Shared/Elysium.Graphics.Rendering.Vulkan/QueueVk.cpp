#include "QueueVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FENCEVK
#include "FenceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SEMAPHOREVK
#include "SemaphoreVk.hpp"
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Graphics::Rendering::Vulkan::QueueVk::QueueVk(const LogicalDeviceVk& LogicalDevice, const Elysium::Core::uint32_t FamilyIndex, Elysium::Core::uint32_t Index)
	: _LogicalDevice(LogicalDevice), _NativeQueueHandle(VK_NULL_HANDLE), _FamilyIndex(FamilyIndex), _Index(Index)
{
	VkDeviceQueueInfo2 DeviceQueueInfo = VkDeviceQueueInfo2();
	DeviceQueueInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2;
	DeviceQueueInfo.pNext = nullptr;
	DeviceQueueInfo.flags = 0;
	DeviceQueueInfo.queueFamilyIndex = _FamilyIndex;
	DeviceQueueInfo.queueIndex = _Index;

	vkGetDeviceQueue2(_LogicalDevice._NativeLogicalDeviceHandle, &DeviceQueueInfo, &_NativeQueueHandle);
	//vkGetDeviceQueue(_LogicalDevice._NativeLogicalDeviceHandle, _FamilyIndex, _Index, &_NativeQueueHandle);
}
Elysium::Graphics::Rendering::Vulkan::QueueVk::~QueueVk()
{
	// queues are implicitly cleaned up when the logical device is destroyed so there is nothing to do here
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::QueueVk::GetFamilyIndex() const
{
	return _FamilyIndex;
}

void Elysium::Graphics::Rendering::Vulkan::QueueVk::Submit(const INativeSemaphore& PresentSemaphore, const INativeSemaphore& RenderSemaphore, const INativeFence& Fence)
{
	const SemaphoreVk& VkPresentSemaphore = dynamic_cast<const SemaphoreVk&>(PresentSemaphore);
	const SemaphoreVk& VkRenderSemaphore = dynamic_cast<const SemaphoreVk&>(RenderSemaphore);
	const FenceVk& VkFence = dynamic_cast<const FenceVk&>(Fence);

	VkPipelineStageFlags WaitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

	VkSubmitInfo SubmitInfo = VkSubmitInfo();
	SubmitInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
	SubmitInfo.pNext = nullptr;
	SubmitInfo.pWaitDstStageMask = &WaitStage;
	SubmitInfo.waitSemaphoreCount = 1;
	SubmitInfo.pWaitSemaphores = &VkPresentSemaphore._NativeSemaphoreHandle;
	SubmitInfo.signalSemaphoreCount = 1;
	SubmitInfo.pSignalSemaphores = &VkRenderSemaphore._NativeSemaphoreHandle;
	SubmitInfo.commandBufferCount = 0;
	SubmitInfo.pCommandBuffers = nullptr;

	VkResult Result;
	if ((Result = vkQueueSubmit(_NativeQueueHandle, 1, &SubmitInfo, VkFence._NativeFenceHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}

void Elysium::Graphics::Rendering::Vulkan::QueueVk::Wait() const
{
	VkResult Result;
	if ((Result = vkQueueWaitIdle(_NativeQueueHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}
