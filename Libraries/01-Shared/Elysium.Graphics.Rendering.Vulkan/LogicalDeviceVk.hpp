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

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_DEVICEQUEUECREATEINFOVK
#include "DeviceQueueCreateInfoVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICEVK
#include "PhysicalDeviceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PRESENTATIONPARAMETERSVK
#include "PresentationParametersVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class CommandBufferVk;
	class CommandPoolVk;
	class DepthBufferVk;
	class FenceVk;
	class FramebufferVk;
	class QueueVk;
	class RenderPassVk;
	class SemaphoreVk;
	class ShaderModuleVk;
	class SwapchainVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API LogicalDeviceVk final
	{
		friend class CommandBufferVk;
		friend class CommandPoolVk;
		friend class DepthBufferVk;
		friend class FenceVk;
		friend class FramebufferVk;
		friend class GraphicsPipelineVk;
		friend class PhysicalDeviceVk;
		friend class QueueVk;
		friend class RenderPassVk;
		friend class SemaphoreVk;
		friend class ShaderModuleVk;
		friend class SwapchainVk;
	public:
		LogicalDeviceVk(const PhysicalDeviceVk& PhysicalDevice, PresentationParametersVk& PresentationParameters);
		LogicalDeviceVk(const LogicalDeviceVk& Source) = delete;
		LogicalDeviceVk(LogicalDeviceVk&& Right) noexcept = delete;
		~LogicalDeviceVk();

		LogicalDeviceVk& operator=(const LogicalDeviceVk& Source) = delete;
		LogicalDeviceVk& operator=(LogicalDeviceVk&& Right) noexcept = delete;

		PresentationParametersVk& GetPresentationParameters() const;

		void Wait() const;
	private:
		const PhysicalDeviceVk& _PhysicalDevice;
		PresentationParametersVk& _PresentationParameters;
		VkDevice _NativeLogicalDeviceHandle;
	};
}
#endif
