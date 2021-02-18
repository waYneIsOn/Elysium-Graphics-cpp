#include "SemaphoreVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::SemaphoreVk::SemaphoreVk(const LogicalDeviceVk& LogicalDevice)
	: _LogicalDevice(LogicalDevice), _NativeSemaphoreHandle(VK_NULL_HANDLE)
{
	VkSemaphoreCreateInfo CreateInfo = VkSemaphoreCreateInfo();
	CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	CreateInfo.pNext = nullptr;
	CreateInfo.flags = 0;

	VkResult Result;
	if ((Result = vkCreateSemaphore(_LogicalDevice._NativeLogicalDeviceHandle, &CreateInfo, nullptr, &_NativeSemaphoreHandle)) != VK_NULL_HANDLE)
	{
		throw ExceptionVk(Result);
	}
}

Elysium::Graphics::Rendering::Vulkan::SemaphoreVk::~SemaphoreVk()
{
	if (_NativeSemaphoreHandle != VK_NULL_HANDLE)
	{
		vkDestroySemaphore(_LogicalDevice._NativeLogicalDeviceHandle, _NativeSemaphoreHandle, nullptr);
		_NativeSemaphoreHandle = VK_NULL_HANDLE;
	}
}

void Elysium::Graphics::Rendering::Vulkan::SemaphoreVk::Wait(const Elysium::Core::uint64_t Timeout)
{
	throw 1;
	/*
	Elysium::Core::uint64_t Bla[1];
	Bla[0] = 2;

	VkSemaphoreWaitInfo WaitInfo = VkSemaphoreWaitInfo();
	WaitInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO;
	WaitInfo.flags = 0;
	WaitInfo.pNext = nullptr;
	WaitInfo.pSemaphores = &_NativeSemaphoreHandle;
	WaitInfo.semaphoreCount = 1;
	// ToDo:
	WaitInfo.pValues = &Bla[0];

	VkResult Result;
	if ((Result = vkWaitSemaphores(_LogicalDevice._NativeLogicalDeviceHandle, &WaitInfo, Timeout)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
	*/
}
