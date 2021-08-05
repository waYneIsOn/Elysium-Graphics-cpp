/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVESHADERMODULE
#define ELYSIUM_GRAPHICS_RENDERING_INATIVESHADERMODULE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API INativeShaderModule
	{
	public:
		virtual ~INativeShaderModule() { }
	};
}
#endif
