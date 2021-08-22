#include "SemaphoreVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSDEVICEVK
#include "GraphicsDeviceVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::SemaphoreVk::SemaphoreVk(const GraphicsDeviceVk& GraphicsDevice)
	: _GraphicsDevice(GraphicsDevice), _NativeSemaphoreHandle(CreateNativeSemaphore())
{ }
Elysium::Graphics::Rendering::Vulkan::SemaphoreVk::~SemaphoreVk()
{
	DestroyNativeSemaphore();
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

VkSemaphore Elysium::Graphics::Rendering::Vulkan::SemaphoreVk::CreateNativeSemaphore()
{
	VkSemaphoreCreateInfo CreateInfo = VkSemaphoreCreateInfo();
	CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	CreateInfo.pNext = nullptr;
	CreateInfo.flags = 0;

	VkSemaphore Semaphore;
	VkResult Result;
	if ((Result = vkCreateSemaphore(_GraphicsDevice._NativeLogicalDeviceHandle, &CreateInfo, nullptr, &Semaphore)) != VK_NULL_HANDLE)
	{
		throw ExceptionVk(Result);
	}

	return Semaphore;
}

void Elysium::Graphics::Rendering::Vulkan::SemaphoreVk::DestroyNativeSemaphore()
{
	if (_NativeSemaphoreHandle != VK_NULL_HANDLE)
	{
		vkDestroySemaphore(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeSemaphoreHandle, nullptr);
		_NativeSemaphoreHandle = VK_NULL_HANDLE;
	}
}
