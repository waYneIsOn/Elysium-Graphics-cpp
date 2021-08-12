/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_RENDERPASS
#define ELYSIUM_GRAPHICS_RENDERING_RENDERPASS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVERENDERPASS
#include "INativeRenderPass.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class GraphicsDevice;

	class ELYSIUM_GRAPHICS_API RenderPass final
	{
		friend class CommandBuffer;
		friend class FrameBuffer;
		friend class GraphicsDevice;
		friend class GraphicsPipeline;
	public:
		RenderPass(const GraphicsDevice& GraphicsDevice);
		RenderPass(const RenderPass& Source) = delete;
		RenderPass(RenderPass&& Right) noexcept = delete;
		~RenderPass();

		RenderPass& operator=(const RenderPass& Source) = delete;
		RenderPass& operator=(RenderPass&& Right) noexcept = delete;
	private:
		const GraphicsDevice& _GraphicsDevice;

		Native::INativeRenderPass* _NativeRenderPass;
	};
}
#endif
