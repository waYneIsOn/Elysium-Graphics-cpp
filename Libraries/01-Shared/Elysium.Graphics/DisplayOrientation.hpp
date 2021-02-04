/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_DISPLAYORIENTATION
#define ELYSIUM_GRAPHICS_DISPLAYORIENTATION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Graphics
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class DisplayOrientation : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class DisplayOrientation
#else
#error "undefined os"
#endif
	{
		// ...
		Default = 0,

		// ...
		LandscapeLeft = 1,

		// ...
		LandscapeRight = 2,

		// ...
		Portrait = 3
	};
}
#endif
