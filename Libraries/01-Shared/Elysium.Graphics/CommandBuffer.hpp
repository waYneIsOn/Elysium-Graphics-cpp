/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_COMMANDBUFFER
#define ELYSIUM_GRAPHICS_RENDERING_COMMANDBUFFER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_FRAMEBUFFER
#include "Framebuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_GRAPHICSPIPELINE
#include "GraphicsPipeline.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVECOMMANDBUFFER
#include "INativeCommandBuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_RENDERPASS
#include "RenderPass.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class CommandPool;
	class GraphicsDevice;
	class Queue;

	class ELYSIUM_GRAPHICS_API CommandBuffer final
	{
		friend class CommandPool;
		friend class Queue;
	public:
		CommandBuffer(const CommandBuffer& Source) = delete;
		CommandBuffer(CommandBuffer&& Right) noexcept = delete;
		~CommandBuffer();

		CommandBuffer& operator=(const CommandBuffer& Source) = delete;
		CommandBuffer& operator=(CommandBuffer&& Right) noexcept = delete;

		void Begin();
		void End();
		void Reset();

		void RecordSecondaryBuffer(const CommandBuffer& CommandBuffer);

		void BeginRenderPass(const RenderPass& RenderPass, const Framebuffer& Framebuffer);
		void EndRenderPass();

		void SetGraphicsPipeline(const GraphicsPipeline& GraphicsPipeline);

		void Draw(Elysium::Core::uint32_t VertexCount, Elysium::Core::uint32_t InstanceCount, Elysium::Core::uint32_t FirstVertex, Elysium::Core::uint32_t FirstInstance);

		void ClearBackBufferImage(const Color ClearColor);
		void ClearDepthImage(const float Depth, const Elysium::Core::int32_t Stencil);
	private:
		CommandBuffer(Native::INativeCommandBuffer* NativeCommandBuffer);

		Native::INativeCommandBuffer* _NativeCommandBuffer;
	};
}
#endif
