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

#ifndef ELYSIUM_CORE_STRING
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_BLITFILTER
#include "BlitFilter.hpp"
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

#ifndef ELYSIUM_GRAPHICS_RENDERING_INDEXBUFFER
#include "IndexBuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_RENDERPASS
#include "RenderPass.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VERTEXBUFFER
#include "VertexBuffer.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class GraphicsDevice;

	class ELYSIUM_GRAPHICS_API CommandBuffer final
	{
		friend class CommandPool;
		friend class Queue;
	private:
		CommandBuffer(Native::INativeCommandBuffer* NativeCommandBuffer);
	public:
		CommandBuffer(const CommandBuffer& Source) = delete;

		CommandBuffer(CommandBuffer&& Right) noexcept = delete;

		~CommandBuffer();
	public:
		CommandBuffer& operator=(const CommandBuffer& Source) = delete;

		CommandBuffer& operator=(CommandBuffer&& Right) noexcept = delete;
	public:
		/// <summary>
		/// Starts recording a command buffer.
		/// </summary>
		void BeginRecording();

		/// <summary>
		/// Finishes recording a command buffer.
		/// </summary>
		void EndRecording();

		/// <summary>
		/// Resets a command buffer to the initial state.
		/// </summary>
		void Reset();

		void RecordSecondaryBuffer(const CommandBuffer& CommandBuffer);

		void RecordBeginRenderPass(const RenderPass& RenderPass, const FrameBuffer& FrameBuffer, const Color& ClearColor, const float Depth, 
			const Elysium::Core::uint32_t Stencil);
		void RecordEndRenderPass();

		void RecordSetGraphicsPipeline(const GraphicsPipeline& GraphicsPipeline);

		void RecordSetVertexBuffer(const VertexBuffer& VertexBuffer);

		void RecordSetIndexBuffer(const IndexBuffer& IndexBuffer);

		/// <summary>
		/// Renders a sequence of non-indexed geometric primitives of the specified type from the current set of data input streams.
		/// </summary>
		/// <param name="VertexCount"></param>
		/// <param name="InstanceCount"></param>
		/// <param name="FirstVertex"></param>
		/// <param name="FirstInstance"></param>
		void RecordDrawPrimitives(const Elysium::Core::uint32_t VertexCount, const Elysium::Core::uint32_t InstanceCount, 
			const Elysium::Core::uint32_t FirstVertex, const Elysium::Core::uint32_t FirstInstance);

		/// <summary>
		/// Renders the specified geometric primitive, based on indexing into an array of vertices.
		/// </summary>
		/// <param name="PrimitiveType"></param>
		/// <param name="BaseVertex"></param>
		/// <param name="MinimumVertexIndex"></param>
		/// <param name="NumberVertices"></param>
		/// <param name="Startindex"></param>
		/// <param name="PrimitiveCount"></param>
		void RecordDrawIndexedPrimitives(const PrimitiveType PrimitiveType, const Elysium::Core::uint32_t BaseVertex,
			const Elysium::Core::uint32_t MinimumVertexIndex, const Elysium::Core::uint32_t NumberVertices, const Elysium::Core::uint32_t StartIndex,
			const Elysium::Core::uint32_t NumberIndices);

		/// <summary>
		/// Copies a given framebuffer to swapchain, potentially performing format conversion.
		/// </summary>
		/// <param name="FrameBuffer"></param>
		/// <param name="Filter"></param>
		void RecordBlit(const FrameBuffer& FrameBuffer, const BlitFilter Filter);

		/// <summary>
		/// Clears color image of back buffer.
		/// </summary>
		/// <param name="ClearColor"></param>
		void RecordClearBackBufferColorImage(const Color ClearColor);

		/// <summary>
		/// Fills depth image of back buffer.
		/// </summary>
		/// <param name="Depth"></param>
		/// <param name="Stencil"></param>
		void RecordClearBackBufferDepthImage(const float Depth, const Elysium::Core::uint32_t Stencil);
	private:
		Native::INativeCommandBuffer* _NativeCommandBuffer;
	};
}
#endif
