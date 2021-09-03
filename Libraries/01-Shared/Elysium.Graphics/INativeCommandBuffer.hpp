/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVECOMMANDBUFFER
#define ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVECOMMANDBUFFER

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

#ifndef ELYSIUM_GRAPHICS_RENDERING_BLITFILTER
#include "BlitFilter.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEFRAMEBUFFER
#include "INativeFrameBuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSPIPELINE
#include "INativeGraphicsPipeline.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVERENDERPASS
#include "INativeRenderPass.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVESHADERMODULE
#include "INativeShaderModule.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEVERTEXBUFFER
#include "INativeVertexBuffer.hpp"
#endif

namespace Elysium::Graphics::Rendering::Native
{
	class ELYSIUM_GRAPHICS_API INativeCommandBuffer
	{
	public:
		virtual ~INativeCommandBuffer() { }

		virtual void BeginRecording() = 0;
		virtual void EndRecording() = 0;
		virtual void Reset() = 0;

		virtual void RecordSecondaryBuffer(const INativeCommandBuffer& CommandBuffer) = 0;

		virtual void RecordBeginRenderPass(const INativeRenderPass& RenderPass, const INativeFrameBuffer& FrameBuffer, const Color& ClearColor, 
			const float Depth, const Elysium::Core::uint32_t Stencil) = 0;
		virtual void RecordEndRenderPass() = 0;

		virtual void RecordSetGraphicsPipeline(const INativeGraphicsPipeline& GraphicsPipeline) = 0;

		virtual void RecordSetVertexBuffer(const INativeVertexBuffer& VertexBuffer) = 0;

		virtual void RecordDraw(Elysium::Core::uint32_t VertexCount, Elysium::Core::uint32_t InstanceCount, Elysium::Core::uint32_t FirstVertex, Elysium::Core::uint32_t FirstInstance) = 0;
		//virtual void RecordDrawPrimitives() = 0;
		//virtual void RecordDrawIndexedPrimitives() = 0;

		virtual void RecordBlit(const INativeFrameBuffer& FrameBuffer, const BlitFilter Filter) = 0;

		virtual void RecordClearBackBufferColorImage(const Color& ClearColor) = 0;
		virtual void RecordClearBackBufferDepthImage(const float Depth, const Elysium::Core::uint32_t Stencil) = 0;
	};
}
#endif
