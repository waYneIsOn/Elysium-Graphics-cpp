/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FENCEVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_FENCEVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEFENCE
#include "../Elysium.Graphics/INativeFence.hpp"
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

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API FenceVk final : public INativeFence
	{
		friend class LogicalDeviceVk;
		friend class SwapchainVk;
	public:
		FenceVk(const FenceVk& Source) = delete;
		FenceVk(FenceVk&& Right) noexcept = delete;
		virtual ~FenceVk();

		FenceVk& operator=(const FenceVk& Source) = delete;
		FenceVk& operator=(FenceVk&& Right) noexcept = delete;

		virtual void Wait(const Elysium::Core::uint64_t Timeout) override;
		virtual void Reset() override;
	private:
		FenceVk(const VkDevice NativeLogicalDeviceHandle, const VkFence NativeFenceHandle);

		const VkDevice _NativeLogicalDeviceHandle;
		const VkFence _NativeFenceHandle;
	};
}
#endif
