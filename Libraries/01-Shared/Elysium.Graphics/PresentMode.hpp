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
		/// 
		/// </summary>
		VerticalSync = 1,

		/// <summary>
		/// 
		/// </summary>
		Immediate = 255,
	};
}
#endif
