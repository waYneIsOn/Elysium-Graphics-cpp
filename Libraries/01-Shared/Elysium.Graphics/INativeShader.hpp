/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVESHADER
#define ELYSIUM_GRAPHICS_RENDERING_INATIVESHADER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API INativeShader
	{
	public:
		virtual ~INativeShader() { }
	};
}
#endif
