/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_LOGICALDEVICEVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_LOGICALDEVICEVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_ILOGICALDEVICE
#include "../Elysium.Graphics/ILogicalDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_DEVICEQUEUECREATEINFOVK
#include "DeviceQueueCreateInfoVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_QUEUEVK
#include "QueueVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEVK
#include "SurfaceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SWAPCHAINVK
#include "SwapchainVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SWAPCHAINCREATEINFOVK
#include "SwapchainCreateInfoVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class PhysicalDeviceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API LogicalDeviceVk final : public ILogicalDevice
	{
		friend class PhysicalDeviceVk;
	public:
		LogicalDeviceVk(const LogicalDeviceVk& Source) = delete;
		LogicalDeviceVk(LogicalDeviceVk&& Right) noexcept = delete;
		virtual ~LogicalDeviceVk();

		LogicalDeviceVk& operator=(const LogicalDeviceVk& Source) = delete;
		LogicalDeviceVk& operator=(LogicalDeviceVk&& Right) noexcept = delete;

		SwapchainVk CreateSwapchain(const SurfaceVk& Surface, const SwapchainCreateInfoVk& SwapchainCreateInfo);

		virtual QueueVk& RetrieveQueue(const Elysium::Core::uint32_t FamilyIndex, const Elysium::Core::uint32_t Index) override;
	private:
		LogicalDeviceVk(const VkDevice NativeLogicalDeviceHandle, Elysium::Core::Collections::Template::Array<QueueVk>&& Queues);

		const VkDevice _NativeLogicalDeviceHandle;
		Core::Collections::Template::Array<QueueVk> _Queues;
	};
}
#endif
