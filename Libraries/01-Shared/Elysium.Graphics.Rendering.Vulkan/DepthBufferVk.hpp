/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_DEPTHBUFFERVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_DEPTHBUFFERVK

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
	class CommandBufferVk;
	class LogicalDeviceVk;
	class SurfaceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API DepthBufferVk final
	{
		friend class CommandBufferVk;
	public:
		DepthBufferVk(const LogicalDeviceVk& LogicalDevice, SurfaceVk& Surface);
		DepthBufferVk(const DepthBufferVk& Source) = delete;
		DepthBufferVk(DepthBufferVk&& Right) noexcept = delete;
		~DepthBufferVk();

		DepthBufferVk& operator=(const DepthBufferVk& Source) = delete;
		DepthBufferVk& operator=(DepthBufferVk&& Right) noexcept = delete;
	private:
		const LogicalDeviceVk& _LogicalDevice;
		SurfaceVk& _Surface;

		VkImage _NativeDepthImageHandle;
		VkDeviceMemory _NativeDepthImageMemoryHandle;
		VkImageView _NativeDepthImageViewHandle;

		void DestroyResources();
		void CreateResources();
		void RecreateDepthBuffer();

		void Surface_OnSizeChanged(const Elysium::Graphics::Rendering::Vulkan::SurfaceVk& Sender);
	};
}
#endif
