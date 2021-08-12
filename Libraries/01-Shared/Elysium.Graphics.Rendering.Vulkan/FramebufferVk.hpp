/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FRAMEBUFFERVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_FRAMEBUFFERVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEFRAMEBUFFER
#include "../Elysium.Graphics/INativeFrameBuffer.hpp"
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

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_RENDERPASSVK
#include "RenderPassVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEVK
#include "SurfaceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SWAPCHAINVK
#include "SwapchainVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API FrameBufferVk final : public Native::INativeFrameBuffer
	{
		friend class CommandBufferVk;
	public:
		FrameBufferVk(const GraphicsDeviceVk& GraphicsDevice, const RenderPassVk& RenderPass, SurfaceVk& Surface);
		FrameBufferVk(const FrameBufferVk& Source) = delete;
		FrameBufferVk(FrameBufferVk&& Right) noexcept = delete;
		virtual ~FrameBufferVk();

		FrameBufferVk& operator=(const FrameBufferVk& Source) = delete;
		FrameBufferVk& operator=(FrameBufferVk&& Right) noexcept = delete;
	private:
		const GraphicsDeviceVk& _GraphicsDevice;
		const RenderPassVk& _RenderPass;
		SurfaceVk& _Surface;
		Elysium::Core::Collections::Template::Array<VkFramebuffer> _NativeSwapchainFramebufferHandles;

		void CreateFramebuffers();
		void DestroyFramebuffers();

		void Surface_OnSizeChanged(const Elysium::Graphics::Rendering::Vulkan::SurfaceVk& Sender);
	};
}
#endif
