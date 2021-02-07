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

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVELOGICALDEVICE
#include "../Elysium.Graphics/INativeLogicalDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_DEVICEQUEUECREATEINFOVK
#include "DeviceQueueCreateInfoVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FENCEVK
#include "FenceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PRESENTATIONPARAMETERSVK
#include "PresentationParametersVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_QUEUEVK
#include "QueueVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SEMAPHOREVK
#include "SemaphoreVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEVK
#include "SurfaceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SWAPCHAINVK
#include "SwapchainVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class PhysicalDeviceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API LogicalDeviceVk final : public INativeLogicalDevice
	{
		friend class PhysicalDeviceVk;
	public:
		LogicalDeviceVk(const LogicalDeviceVk& Source) = delete;
		LogicalDeviceVk(LogicalDeviceVk&& Right) noexcept = delete;
		virtual ~LogicalDeviceVk();

		LogicalDeviceVk& operator=(const LogicalDeviceVk& Source) = delete;
		LogicalDeviceVk& operator=(LogicalDeviceVk&& Right) noexcept = delete;

		SwapchainVk CreateSwapchain(const PresentationParametersVk& PresentationParameter);

		virtual FenceVk& RetrieveFence() override;
		virtual SemaphoreVk& RetrieveSemaphore() override;
		virtual QueueVk& RetrieveQueue(const Elysium::Core::uint32_t FamilyIndex, const Elysium::Core::uint32_t Index) override;

		virtual void Wait() override;
		FenceVk CreateFenceTest();
		SemaphoreVk CreateSemaphoreTest();
	private:
		LogicalDeviceVk(const VkDevice NativeLogicalDeviceHandle, Elysium::Core::Collections::Template::Array<QueueVk>&& Queues);

		const VkDevice _NativeLogicalDeviceHandle;
		Core::Collections::Template::Array<QueueVk> _Queues;
	};
}
#endif
