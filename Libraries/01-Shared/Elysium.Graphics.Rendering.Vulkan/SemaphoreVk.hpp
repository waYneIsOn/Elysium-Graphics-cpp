/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SEMAPHOREVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_SEMAPHOREVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVESEMAPHORE
#include "../Elysium.Graphics/INativeSemaphore.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class LogicalDeviceVk;
	class SwapchainVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API SemaphoreVk final : public INativeSemaphore
	{
		friend class LogicalDeviceVk;
		friend class SwapchainVk;
	public:
		SemaphoreVk(const SemaphoreVk& Source) = delete;
		SemaphoreVk(SemaphoreVk&& Right) noexcept = delete;
		virtual ~SemaphoreVk();

		SemaphoreVk& operator=(const SemaphoreVk& Source) = delete;
		SemaphoreVk& operator=(SemaphoreVk&& Right) noexcept = delete;

		virtual void Wait(const Elysium::Core::uint64_t Timeout) override;
	private:
		SemaphoreVk(const VkDevice NativeLogicalDeviceHandle, const VkSemaphore NativeSemaphoreHandle);

		const VkDevice _NativeLogicalDeviceHandle;
		const VkSemaphore _NativeSemaphoreHandle;
	};
}
#endif
