/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_PRESENTMODE
#define ELYSIUM_GRAPHICS_PRESENTMODE

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
	enum class PresentMode : Elysium::Core::uint8_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class PresentMode
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// Present a frame whenever the display-device allows it.
		/// </summary>
		VerticalSync = 1,

		/// <summary>
		/// (GSync/FreeSync)
		/// </summary>
		//Adaptive = 2,

		/// <summary>
		/// Presents a frame whenever possible. (Will most likely cause tearing.)
		/// </summary>
		Immediate = 255,
	};
}
#endif
