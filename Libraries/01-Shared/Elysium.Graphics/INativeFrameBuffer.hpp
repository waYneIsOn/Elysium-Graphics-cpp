/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEFRAMEBUFFER
#define ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEFRAMEBUFFER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_SURFACEFORMAT
#include "SurfaceFormat.hpp"
#endif

namespace Elysium::Graphics::Rendering::Native
{
	class ELYSIUM_GRAPHICS_API INativeFrameBuffer
	{
	public:
		virtual ~INativeFrameBuffer() { }

		virtual const SurfaceFormat GetSurfaceFormat() const = 0;
	};
}
#endif
