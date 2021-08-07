/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_RENDERPASSVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_RENDERPASSVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVERENDERPASS
#include "../Elysium.Graphics/INativeRenderPass.hpp"
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
	class FramebufferVk;
	class LogicalDeviceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API RenderPassVk final : public INativeRenderPass
	{
		friend class CommandBufferVk;
		friend class FramebufferVk;
		friend class GraphicsPipelineVk;
		friend class LogicalDeviceVk;
	public:
		RenderPassVk(const LogicalDeviceVk& LogicalDevice);
		RenderPassVk(const RenderPassVk& Source) = delete;
		RenderPassVk(RenderPassVk&& Right) noexcept = delete;
		virtual ~RenderPassVk();

		RenderPassVk& operator=(const RenderPassVk& Source) = delete;
		RenderPassVk& operator=(RenderPassVk&& Right) noexcept = delete;
	private:
		const LogicalDeviceVk& _LogicalDevice;
		VkRenderPass _NativeRenderPassHandle;
	};
}
#endif
