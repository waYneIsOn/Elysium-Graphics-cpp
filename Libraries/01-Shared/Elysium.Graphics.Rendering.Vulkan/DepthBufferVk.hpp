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

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API DepthBufferVk final : public INativeDepthBuffer
	{
	public:
		DepthBufferVk(const DepthBufferVk& Source) = delete;
		DepthBufferVk(DepthBufferVk&& Right) noexcept = delete;
		virtual ~DepthBufferVk();

		DepthBufferVk& operator=(const DepthBufferVk& Source) = delete;
		DepthBufferVk& operator=(DepthBufferVk&& Right) noexcept = delete;
	private:
		DepthBufferVk(const VkDevice NativeLogicalDeviceHandle);

		const VkDevice _NativeLogicalDeviceHandle;

		const VkImage _NativeDepthImageHandle = VK_NULL_HANDLE;
		const VkDeviceMemory _NativeDepthImageMemoryHandle = VK_NULL_HANDLE;
		const VkImageView _NativeDepthImageViewHandle = VK_NULL_HANDLE;
	};
}
#endif
