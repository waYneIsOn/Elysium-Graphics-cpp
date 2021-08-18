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

		// ToDo: a framebuffer should hold it's own images to be rendered to which then can be copied to the swapchain images before presentation
		//Elysium::Core::Collections::Template::Array<VkImage> _NativeImages;
		//Elysium::Core::Collections::Template::Array<VkImageView> _NativeImageViews;
		Elysium::Core::Collections::Template::Array<VkFramebuffer> _NativeFramebuffers;

		void CreateFramebuffers();
		void DestroyFramebuffers();

		void Surface_OnSizeChanged(const Elysium::Graphics::Rendering::Vulkan::SurfaceVk& Sender);
	};
}
#endif
