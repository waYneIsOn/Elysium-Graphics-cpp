#include "QueueVk.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Graphics::Rendering::Vulkan::QueueVk::~QueueVk()
{
	// queues are implicitly cleaned up when the logical device is destroyed so there is nothing to do here
}

Elysium::Graphics::Rendering::Vulkan::QueueVk::QueueVk()
	: _NativeQueueHandle(VK_NULL_HANDLE), _FamilyIndex(-1), _Index(-1)
{ }
