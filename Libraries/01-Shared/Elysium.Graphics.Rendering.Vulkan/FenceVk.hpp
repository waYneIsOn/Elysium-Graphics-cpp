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

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_LOGICALDEVICEVK
#include "LogicalDeviceVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API FenceVk final : public INativeFence
	{
	public:
		FenceVk(const LogicalDeviceVk& LogicalDevice);
		FenceVk(const FenceVk& Source) = delete;
		FenceVk(FenceVk&& Right) noexcept = delete;
		virtual ~FenceVk();

		FenceVk& operator=(const FenceVk& Source) = delete;
		FenceVk& operator=(FenceVk&& Right) noexcept = delete;

		virtual void Wait(const Elysium::Core::uint64_t Timeout) const override;
		virtual void Reset() override;
	private:
		const LogicalDeviceVk& _LogicalDevice;
		VkFence _NativeFenceHandle;
	};
}
#endif
