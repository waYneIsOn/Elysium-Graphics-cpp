/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVECOMMANDBUFFER
#define ELYSIUM_GRAPHICS_RENDERING_INATIVECOMMANDBUFFER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_COLOR
#include "Color.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEFRAMEBUFFER
#include "INativeFrameBuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVERENDERPASS
#include "INativeRenderPass.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class INativeRenderPass;

	class ELYSIUM_GRAPHICS_API INativeCommandBuffer
	{
	public:
		virtual ~INativeCommandBuffer() { }

		virtual void Begin() = 0;
		virtual void End() = 0;
		virtual void Reset() = 0;

		virtual void BeginRenderPass(const INativeRenderPass& RenderPass, const INativeFramebuffer& FrameBuffer) = 0;
		virtual void EndRenderPass() = 0;

		virtual void ClearBackBufferImage(const Color& ClearColor) = 0;
		virtual void ClearDepthImage(const float Depth, const Elysium::Core::int32_t Stencil) = 0;

		//virtual void SetVertexShader() = 0;
	};
}
#endif
