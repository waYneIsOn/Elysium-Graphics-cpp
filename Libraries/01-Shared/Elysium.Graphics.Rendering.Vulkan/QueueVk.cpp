#include "QueueVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Graphics::Rendering::Vulkan::QueueVk::~QueueVk()
{
	// queues are implicitly cleaned up when the logical device is destroyed so there is nothing to do here
}

void Elysium::Graphics::Rendering::Vulkan::QueueVk::Wait()
{
	VkResult Result;
	if ((Result = vkQueueWaitIdle(_NativeQueueHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}

Elysium::Graphics::Rendering::Vulkan::QueueVk::QueueVk()
	: _NativeQueueHandle(VK_NULL_HANDLE), _FamilyIndex(-1), _Index(-1)
{ }
