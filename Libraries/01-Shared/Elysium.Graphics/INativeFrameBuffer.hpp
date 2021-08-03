/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEFRAMEBUFFER
#define ELYSIUM_GRAPHICS_RENDERING_INATIVEFRAMEBUFFER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API INativeFramebuffer
	{
	public:
		virtual ~INativeFramebuffer() { }
	};
}
#endif
