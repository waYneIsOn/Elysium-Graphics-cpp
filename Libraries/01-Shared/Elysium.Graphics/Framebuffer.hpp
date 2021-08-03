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

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEFRAMEBUFFER
#include "INativeFramebuffer.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class CommandBuffer;
	class GraphicsDevice;

	class ELYSIUM_GRAPHICS_API Framebuffer final
	{
		friend class CommandBuffer;
		friend class GraphicsDevice;
	public:
		Framebuffer(const Framebuffer& Source) = delete;
		Framebuffer(Framebuffer&& Right) noexcept = delete;
		~Framebuffer();

		Framebuffer& operator=(const Framebuffer& Source) = delete;
		Framebuffer& operator=(Framebuffer&& Right) noexcept = delete;
	private:
		Framebuffer(INativeFramebuffer& NativeFramebuffer);

		INativeFramebuffer& _NativeFramebuffer;
	};
}
#endif
