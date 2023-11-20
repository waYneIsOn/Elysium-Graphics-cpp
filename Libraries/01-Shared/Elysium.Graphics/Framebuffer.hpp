/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_FRAMEBUFFER
#define ELYSIUM_GRAPHICS_RENDERING_FRAMEBUFFER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEFRAMEBUFFER
#include "INativeFrameBuffer.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class GraphicsDevice;
	class RenderPass;

	class ELYSIUM_GRAPHICS_API FrameBuffer final
	{
		friend class CommandBuffer;
		friend class GraphicsDevice;
	public:
		FrameBuffer(const GraphicsDevice& GraphicsDevice, const RenderPass& RenderPass);

		FrameBuffer(const FrameBuffer& Source) = delete;

		FrameBuffer(FrameBuffer&& Right) noexcept = delete;

		~FrameBuffer();
	public:
		FrameBuffer& operator=(const FrameBuffer& Source) = delete;

		FrameBuffer& operator=(FrameBuffer&& Right) noexcept = delete;
	public:
		const Elysium::Core::uint32_t GetWidth() const;

		const Elysium::Core::uint32_t GetHeight() const;

		const Elysium::Core::uint32_t GetDepth() const;
	private:
		const GraphicsDevice& _GraphicsDevice;

		Native::INativeFrameBuffer* _NativeFrameBuffer;
	};
}
#endif
