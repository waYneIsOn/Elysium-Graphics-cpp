#include "QueueVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FENCEVK
#include "FenceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSDEVICEVK
#include "GraphicsDeviceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SEMAPHOREVK
#include "SemaphoreVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::QueueVk::QueueVk(const GraphicsDeviceVk& GraphicsDevice, const Elysium::Core::uint32_t FamilyIndex, Elysium::Core::uint32_t Index)
	: _GraphicsDevice(GraphicsDevice), _FamilyIndex(FamilyIndex), _Index(Index), _NativeQueueHandle(RetrieveNativeQueue())
{ }
Elysium::Graphics::Rendering::Vulkan::QueueVk::~QueueVk()
{
	// queues are implicitly cleaned up when the logical device is destroyed so there is nothing to do here
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::QueueVk::GetFamilyIndex() const
{
	return _FamilyIndex;
}

Elysium::Graphics::Rendering::Native::INativeCommandPool* Elysium::Graphics::Rendering::Vulkan::QueueVk::CreateCommandPool()
{
	return new CommandPoolVk(_GraphicsDevice, *this);
}

void Elysium::Graphics::Rendering::Vulkan::QueueVk::Submit(const Native::INativeCommandBuffer& CommmandBuffer, const Native::INativeSemaphore& PresentSemaphore, const Native::INativeSemaphore& RenderSemaphore, const Native::INativeFence& Fence)
{
	const CommandBufferVk& VkCommandBuffer = static_cast<const CommandBufferVk&>(CommmandBuffer);
	const SemaphoreVk& VkPresentSemaphore = static_cast<const SemaphoreVk&>(PresentSemaphore);
	const SemaphoreVk& VkRenderSemaphore = static_cast<const SemaphoreVk&>(RenderSemaphore);
	const FenceVk& VkFence = static_cast<const FenceVk&>(Fence);

	VkPipelineStageFlags WaitStage = VkPipelineStageFlagBits::VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

	VkSubmitInfo SubmitInfo = VkSubmitInfo();
	SubmitInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
	SubmitInfo.pNext = nullptr;
	SubmitInfo.pWaitDstStageMask = &WaitStage;
	SubmitInfo.waitSemaphoreCount = 1;
	SubmitInfo.pWaitSemaphores = &VkPresentSemaphore._NativeSemaphoreHandle;
	SubmitInfo.signalSemaphoreCount = 1;
	SubmitInfo.pSignalSemaphores = &VkRenderSemaphore._NativeSemaphoreHandle;
	SubmitInfo.commandBufferCount = VkCommandBuffer._NativeCommandBufferHandles.GetLength();
	SubmitInfo.pCommandBuffers = &VkCommandBuffer._NativeCommandBufferHandles[0];

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

const VkQueue Elysium::Graphics::Rendering::Vulkan::QueueVk::RetrieveNativeQueue()
{
	VkDeviceQueueInfo2 DeviceQueueInfo = VkDeviceQueueInfo2();
	DeviceQueueInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2;
	DeviceQueueInfo.pNext = nullptr;
	DeviceQueueInfo.flags = 0;
	DeviceQueueInfo.queueFamilyIndex = _FamilyIndex;
	DeviceQueueInfo.queueIndex = _Index;

	VkQueue NativeQueueHandle;
	vkGetDeviceQueue2(_GraphicsDevice._NativeLogicalDeviceHandle, &DeviceQueueInfo, &NativeQueueHandle);
	if (_NativeQueueHandle == VK_NULL_HANDLE)
	{
		throw ExceptionVk(VK_ERROR_UNKNOWN);
	}

	return NativeQueueHandle;
}
