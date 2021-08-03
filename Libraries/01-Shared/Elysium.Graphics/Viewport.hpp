/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VIEWPORT
#define ELYSIUM_GRAPHICS_RENDERING_VIEWPORT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEVIEWPORT
#include "INativeViewport.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API Viewport final
	{
	public:
		Viewport(const Viewport& Source) = delete;
		Viewport(Viewport&& Right) noexcept = delete;
		~Viewport();

		Viewport& operator=(const Viewport& Source) = delete;
		Viewport& operator=(Viewport&& Right) noexcept = delete;
	private:
		Viewport(INativeViewport& NativeViewport);

		INativeViewport& _NativeViewport;
	};
}
#endif
