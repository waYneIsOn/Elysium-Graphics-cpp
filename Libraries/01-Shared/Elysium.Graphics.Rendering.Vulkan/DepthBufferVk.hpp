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

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEDEPTHBUFFER
#include "../Elysium.Graphics/INativeDepthBuffer.hpp"
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
	class CommandBufferVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API DepthBufferVk final : public INativeDepthBuffer
	{
		friend class CommandBufferVk;
	public:
		DepthBufferVk(SurfaceVk& Surface, const LogicalDeviceVk& LogicalDevice);
		DepthBufferVk(const DepthBufferVk& Source) = delete;
		DepthBufferVk(DepthBufferVk&& Right) noexcept = delete;
		virtual ~DepthBufferVk();

		DepthBufferVk& operator=(const DepthBufferVk& Source) = delete;
		DepthBufferVk& operator=(DepthBufferVk&& Right) noexcept = delete;
	private:
		SurfaceVk& _Surface;
		const LogicalDeviceVk& _LogicalDevice;

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
