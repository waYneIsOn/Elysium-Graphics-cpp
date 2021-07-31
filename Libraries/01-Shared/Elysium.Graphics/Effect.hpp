/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_GRAPHICS_RENDERING_EFFECT
#define ELYSIUM_GRAPHICS_RENDERING_EFFECT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEEFFECT
#include "INativeEffect.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API Effect
	{
	public:
		//Effect() noexcept;
		Effect(const Effect& Source) noexcept = delete;
		Effect(Effect&& Right) noexcept = delete;
		virtual ~Effect();

		Effect& operator=(const Effect& Source) noexcept = delete;
		Effect& operator=(Effect&& Right) noexcept = delete;
	private:
		//INativeEffect _Effect;
	};
}
#endif
