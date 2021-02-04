/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_QUEUEFAMILYPROPERTYVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_QUEUEFAMILYPROPERTYVK

#ifdef _MSC_VER
#pragma once
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
	class PhysicalDeviceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API QueueFamilyPropertyVk final
	{
		friend class PhysicalDeviceVk;
	public:
		QueueFamilyPropertyVk();
		QueueFamilyPropertyVk(const QueueFamilyPropertyVk& Source) = delete;
		QueueFamilyPropertyVk(QueueFamilyPropertyVk&& Right) noexcept = delete;
		~QueueFamilyPropertyVk();

		QueueFamilyPropertyVk& operator=(const QueueFamilyPropertyVk& Source) = delete;
		QueueFamilyPropertyVk& operator=(QueueFamilyPropertyVk&& Right) noexcept = delete;

		const Elysium::Core::uint32_t GetIndex() const;
		const QueueCapabilitiesVk GetSupportedOperations() const;
		const Elysium::Core::uint32_t GetCount() const;
		const Elysium::Core::uint32_t GetTimestampValidBits() const;
		//const Elysium::Core::uint32_t[3] minImageTransferGranularity() const;
	private:
		Elysium::Core::uint32_t _Index = -1;
		VkQueueFamilyProperties _NativeProperties = VkQueueFamilyProperties();
	};
}
#endif
