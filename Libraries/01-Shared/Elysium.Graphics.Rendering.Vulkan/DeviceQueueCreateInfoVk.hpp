/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_DEVICEQUEUECREATEINFOVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_DEVICEQUEUECREATEINFOVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_QUEUECAPABILITIESVK
#include "QueueCapabilitiesVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API DeviceQueueCreateInfoVk final
	{
	public:
		DeviceQueueCreateInfoVk();
		DeviceQueueCreateInfoVk(Elysium::Core::uint32_t FamilyIndex, Elysium::Core::uint32_t Count, float Priority, QueueCapabilitiesVk Capabilities);
		DeviceQueueCreateInfoVk(const DeviceQueueCreateInfoVk& Source);
		DeviceQueueCreateInfoVk(DeviceQueueCreateInfoVk&& Right) noexcept;
		~DeviceQueueCreateInfoVk();

		DeviceQueueCreateInfoVk& operator=(const DeviceQueueCreateInfoVk& Source);
		DeviceQueueCreateInfoVk& operator=(DeviceQueueCreateInfoVk&& Right) noexcept;
	
		float Priority;
		Elysium::Core::uint32_t FamilyIndex;
		Elysium::Core::uint32_t Count;
		QueueCapabilitiesVk Capabilities;
	};
}
#endif
