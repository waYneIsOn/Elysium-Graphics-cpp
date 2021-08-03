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

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVECOMMANDBUFFER
#include "INativeCommandBuffer.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class CommandPool;
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

		void BeginRenderPass();// (const RenderPass& RenderPass);
		void EndRenderPass();

		void ClearBackBufferImage(const Color ClearColor);
		void ClearDepthImage(const float Depth, const Elysium::Core::int32_t Stencil);
	private:
		CommandBuffer(INativeCommandBuffer* NativeCommandBuffer);

		INativeCommandBuffer* _NativeCommandBuffer;
	};
}
#endif
