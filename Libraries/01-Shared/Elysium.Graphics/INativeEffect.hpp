/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEEFFECT
#define ELYSIUM_GRAPHICS_RENDERING_INATIVEEFFECT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API INativeEffect
	{
	public:
		virtual ~INativeEffect() { }
	};
}
#endif
