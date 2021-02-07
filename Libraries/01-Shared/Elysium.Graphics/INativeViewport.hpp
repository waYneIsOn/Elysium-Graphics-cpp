/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEVIEWPORT
#define ELYSIUM_GRAPHICS_RENDERING_INATIVEVIEWPORT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API INativeViewport
	{
	public:
		virtual ~INativeViewport() { }

		virtual const float GetX() const = 0;
		virtual const float GetY() const = 0;
		virtual const float GetWidth() const = 0;
		virtual const float GetHeight() const = 0;

		virtual const float GetMinDepth() const = 0;
		virtual const float GetMaxDepth() const = 0;

		//virtual const float GetAspectRatio() const = 0;
	};
}
#endif
