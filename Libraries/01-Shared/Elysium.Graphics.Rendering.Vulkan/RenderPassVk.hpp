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

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVERENDERPASS
#include "../Elysium.Graphics/INativeRenderPass.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_SURFACEFORMAT
#include "../Elysium.Graphics/SurfaceFormat.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class GraphicsDeviceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API RenderPassVk final : public Native::INativeRenderPass
	{
		friend class CommandBufferVk;
		friend class FrameBufferVk;
		friend class GraphicsPipelineVk;
	public:
		RenderPassVk(const GraphicsDeviceVk& GraphicsDevice, const SurfaceFormat SurfaceFormat);
		RenderPassVk(const RenderPassVk& Source) = delete;
		RenderPassVk(RenderPassVk&& Right) noexcept = delete;
		virtual ~RenderPassVk();

		RenderPassVk& operator=(const RenderPassVk& Source) = delete;
		RenderPassVk& operator=(RenderPassVk&& Right) noexcept = delete;

		virtual const SurfaceFormat GetSurfaceFormat() const override;
	private:
		const GraphicsDeviceVk& _GraphicsDevice;
		VkFormat _NativeImageFormat;
		VkRenderPass _NativeRenderPassHandle;

		VkRenderPass CreateNativeRenderPass();

		void DestroyNativeRenderPass();
	};
}
#endif
