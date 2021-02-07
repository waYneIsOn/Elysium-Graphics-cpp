/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_BUFFERVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_BUFFERVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEBUFFER
#include "../Elysium.Graphics/INativeBuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_LOGICALDEVICEVK
#include "LogicalDeviceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API BufferVk : public INativeBuffer
	{
	public:
		BufferVk(const BufferVk& Source) = delete;
		BufferVk(BufferVk&& Right) noexcept = delete;
		virtual ~BufferVk();

		BufferVk& operator=(const BufferVk& Source) = delete;
		BufferVk& operator=(BufferVk&& Right) noexcept = delete;
	protected:
		BufferVk(const VkDevice NativeLogicalDeviceHandle, const VkBuffer NativeBufferHandle);

		const VkDevice _NativeLogicalDeviceHandle;
		const VkBuffer _NativeBufferHandle;
	};
}
#endif
