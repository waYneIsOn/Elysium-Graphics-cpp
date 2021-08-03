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

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEFRAMEBUFFER
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
	class CommandBufferVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API FramebufferVk final : public INativeFramebuffer
	{
		friend class CommandBufferVk;
	public:
		FramebufferVk(const LogicalDeviceVk& LogicalDevice, const SwapchainVk& Swapchain, const RenderPassVk& RenderPass);
		FramebufferVk(const FramebufferVk& Source) = delete;
		FramebufferVk(FramebufferVk&& Right) noexcept = delete;
		virtual ~FramebufferVk();

		FramebufferVk& operator=(const FramebufferVk& Source) = delete;
		FramebufferVk& operator=(FramebufferVk&& Right) noexcept = delete;
	private:
		const LogicalDeviceVk& _LogicalDevice;
		const SwapchainVk& _Swapchain;
		const RenderPassVk& _RenderPass;
		SurfaceVk& _Surface;
		Elysium::Core::Collections::Template::Array<VkFramebuffer> _NativeSwapchainFramebufferHandles;

		void CreateFramebuffers();
		void DestroyFramebuffers();

		void Surface_OnSizeChanged(const Elysium::Graphics::Rendering::Vulkan::SurfaceVk& Sender);
	};
}
#endif
