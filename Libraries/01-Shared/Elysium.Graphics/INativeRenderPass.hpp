/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVERENDERPASS
#define ELYSIUM_GRAPHICS_RENDERING_INATIVERENDERPASS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API INativeRenderPass
	{
	public:
		virtual ~INativeRenderPass() { }
	};
}
#endif
