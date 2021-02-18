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

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PRESENTATIONPARAMETERSVK
#include "PresentationParametersVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEVK
#include "SurfaceVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class CommandBufferVk;
	class CommandPoolVk;
	class FenceVk;
	class PhysicalDeviceVk;
	class QueueVk;
	class SemaphoreVk;
	class SwapchainVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API LogicalDeviceVk final : public INativeLogicalDevice
	{
		friend class CommandBufferVk;
		friend class CommandPoolVk;
		friend class FenceVk;
		friend class PhysicalDeviceVk;
		friend class QueueVk;
		friend class SemaphoreVk;
		friend class SwapchainVk;
	public:
		LogicalDeviceVk(const PhysicalDeviceVk& PhysicalDevice, PresentationParametersVk& PresentationParameters);
		LogicalDeviceVk(const LogicalDeviceVk& Source) = delete;
		LogicalDeviceVk(LogicalDeviceVk&& Right) noexcept = delete;
		virtual ~LogicalDeviceVk();

		LogicalDeviceVk& operator=(const LogicalDeviceVk& Source) = delete;
		LogicalDeviceVk& operator=(LogicalDeviceVk&& Right) noexcept = delete;

		virtual const INativePhysicalDevice& GetPhysicalDevice() const override;

		virtual PresentationParametersVk& GetPresentationParameters() const override;

		virtual void Wait() const override;
	private:
		const PhysicalDeviceVk& _PhysicalDevice;
		PresentationParametersVk& _PresentationParameters;

		VkDevice _NativeLogicalDeviceHandle;
	};
}
#endif
