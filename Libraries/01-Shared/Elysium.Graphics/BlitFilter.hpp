/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_BLITFILTER
#define ELYSIUM_GRAPHICS_RENDERING_BLITFILTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/System.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class BlitFilter : Elysium::Core::uint8_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class BlitFilter
#else
#error "undefined os"
#endif
	{
		Nearest = 0,

		Linear = 1,

		Cubic = 2,
	};
}
#endif
