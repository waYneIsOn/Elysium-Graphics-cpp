/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class GraphicsInstanceVk;
	class QueueVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API SurfaceVk final
	{
		friend class GraphicsInstanceVk;
		friend class QueueVk;
	public:
		SurfaceVk(const SurfaceVk& Source) = delete;
		SurfaceVk(SurfaceVk&& Right) noexcept = delete;
		~SurfaceVk();

		SurfaceVk& operator=(const SurfaceVk& Source) = delete;
		SurfaceVk& operator=(SurfaceVk&& Right) noexcept = delete;
	private:
		SurfaceVk(const VkInstance NativeInstanceHandle, const VkSurfaceKHR NativeSurfaceHandle);

		const VkInstance _NativeInstanceHandle;
		const VkSurfaceKHR _NativeSurfaceHandle;
	};
}
#endif
