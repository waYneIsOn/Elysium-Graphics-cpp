/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_PRESENTATION_WINDOWSTYLE
#define ELYSIUM_GRAPHICS_PRESENTATION_WINDOWSTYLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Graphics::Presentation
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class WindowStyle : Elysium::Core::uint8_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class WindowStyle
#else
#error "undefined os"
#endif
	{
		// Only the client area is visible - the title bar and border are not shown.
		None = 0,

		// A window with a single border. This is the default value.
		SingleBorderWindow = 1,

		// A window with a 3-D border.
		ThreeDBorderWindow = 2,

		// A fixed tool window.
		ToolWIndow = 3,
	};
}
#endif
