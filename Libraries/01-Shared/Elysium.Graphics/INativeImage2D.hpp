/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEIMAGE2D
#define ELYSIUM_GRAPHICS_RENDERING_INATIVEIMAGE2D

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEIMAGE
#include "INativeImage.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API INativeImage2D : public INativeImage
	{
	public:
		virtual ~INativeImage2D() { }

		virtual const Elysium::Core::uint32_t& GetWidth() const = 0;
		virtual const Elysium::Core::uint32_t& GetHeight() const = 0;
		//virtual const Elysium::Core::Math::Geometry::Rectangle GetBounds() const = 0;
	};
}
#endif
