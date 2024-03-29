/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_DISPLAYMODE
#define ELYSIUM_GRAPHICS_DISPLAYMODE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/System.hpp"
#endif

namespace Elysium::Graphics
{
	/// <summary>
	/// 
	/// </summary>
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class DisplayMode : Elysium::Core::uint8_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class DisplayMode
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// 
		/// </summary>
		Fullscreen = 0,

		/// <summary>
		/// 
		/// </summary>
		BorderlessWindowed = 1,

		/// <summary>
		/// 
		/// </summary>
		Windowed = 2,
	};
}
#endif
