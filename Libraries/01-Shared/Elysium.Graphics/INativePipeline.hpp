/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEPIPELINE
#define ELYSIUM_GRAPHICS_RENDERING_INATIVEPIPELINE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVESHADERMODULE
#include "INativeShaderModule.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API INativePipeline
	{
	public:
		virtual ~INativePipeline() { }

		virtual void Build() = 0;
	};
}
#endif
