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
	class GraphicsDevice;

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

		/// <summary>
		/// Start recording a command buffer.
		/// </summary>
		void BeginRecording();

		/// <summary>
		/// Finish recording a command buffer.
		/// </summary>
		void EndRecording();

		/// <summary>
		/// Reset a command buffer to the initial state.
		/// </summary>
		void Reset();

		void RecordSecondaryBuffer(const CommandBuffer& CommandBuffer);

		void RecordBeginRenderPass(const RenderPass& RenderPass, const FrameBuffer& FrameBuffer);
		void RecordEndRenderPass();

		void RecordSetGraphicsPipeline(const GraphicsPipeline& GraphicsPipeline);

		/// <summary>
		/// Renders a sequence of non-indexed geometric primitives of the specified type from the current set of data input streams.
		/// </summary>
		/// <param name="VertexCount"></param>
		/// <param name="InstanceCount"></param>
		/// <param name="FirstVertex"></param>
		/// <param name="FirstInstance"></param>
		void RecordDraw(Elysium::Core::uint32_t VertexCount, Elysium::Core::uint32_t InstanceCount, Elysium::Core::uint32_t FirstVertex, Elysium::Core::uint32_t FirstInstance);

		/// <summary>
		/// Copies a given framebuffer to swapchain, potentially performing format conversion.
		/// </summary>
		/// <param name="FrameBuffer"></param>
		void RecordBlit(const FrameBuffer& FrameBuffer);

		/// <summary>
		/// Clear color image of back buffer.
		/// </summary>
		/// <param name="ClearColor"></param>
		void RecordClearBackBufferColorImage(const Color ClearColor);

		/// <summary>
		/// Fill depth image of back buffer.
		/// </summary>
		/// <param name="Depth"></param>
		/// <param name="Stencil"></param>
		void RecordClearBackBufferDepthImage(const float Depth, const Elysium::Core::int32_t Stencil);
	private:
		CommandBuffer(Native::INativeCommandBuffer* NativeCommandBuffer);

		Native::INativeCommandBuffer* _NativeCommandBuffer;
	};
}
#endif
