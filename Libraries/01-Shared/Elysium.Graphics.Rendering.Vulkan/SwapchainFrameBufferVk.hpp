/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SWAPCHAINFRAMEBUFFERVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_SWAPCHAINFRAMEBUFFERVK

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

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSDEVICEVK
#include "GraphicsDeviceVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API SwapchainFrameBufferVk final : public Native::INativeFrameBuffer
	{
		friend class GraphicsDeviceVk;
	public:
		SwapchainFrameBufferVk(const SwapchainFrameBufferVk& Source) = delete;
		SwapchainFrameBufferVk(SwapchainFrameBufferVk&& Right) noexcept = delete;
		virtual ~SwapchainFrameBufferVk();

		SwapchainFrameBufferVk& operator=(const SwapchainFrameBufferVk& Source) = delete;
		SwapchainFrameBufferVk& operator=(SwapchainFrameBufferVk&& Right) noexcept = delete;

		virtual const SurfaceFormat GetSurfaceFormat() const override;
	private:
		SwapchainFrameBufferVk(const GraphicsDeviceVk& GraphicsDevice);

		const GraphicsDeviceVk& _GraphicsDevice;
	};
}
#endif
