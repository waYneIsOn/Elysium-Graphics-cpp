/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_COMMANDBUFFERVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_COMMANDBUFFERVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVECOMMANDBUFFER
#include "../Elysium.Graphics/INativeCommandBuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_COMMANDPOOLVK
#include "CommandPoolVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_LOGICALDEVICEVK
#include "LogicalDeviceVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API CommandBufferVk : public INativeCommandBuffer
	{
	public:
		CommandBufferVk(const CommandPoolVk& CommandPool, const bool IsPrimary);
		CommandBufferVk(const CommandBufferVk& Source) = delete;
		CommandBufferVk(CommandBufferVk&& Right) noexcept = delete;
		virtual ~CommandBufferVk();

		CommandBufferVk& operator=(const CommandBufferVk& Source) = delete;
		CommandBufferVk& operator=(CommandBufferVk&& Right) noexcept = delete;
	private:
		const CommandPoolVk& _CommandPool;
		VkCommandBuffer _NativeCommandBufferHandle;
	};
}
#endif
