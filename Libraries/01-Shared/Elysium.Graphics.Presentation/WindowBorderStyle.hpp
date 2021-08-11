/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_PRESENTATION_WINDOWBORDERSTYLE
#define ELYSIUM_GRAPHICS_PRESENTATION_WINDOWBORDERSTYLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/System.hpp"
#endif

namespace Elysium::Graphics::Presentation
{
	/// <summary>
	/// 
	/// </summary>
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class WindowBorderStyle : Elysium::Core::uint8_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class WindowBorderStyle
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// No border.
		/// </summary>
		None = 0,

		/// <summary>
		/// A fixed, single-line border.
		/// </summary>
		FixedSingle = 1,
		/*
		/// <summary>
		/// 
		/// </summary>
		Fixed3D = 2,

		/// <summary>
		/// 
		/// </summary>
		Sizable = 4,

		/// <summary>
		/// 
		/// </summary>
		FixedToolWindow = 5,

		/// <summary>
		/// 
		/// </summary>
		SizeableToolWindow = 6
		*/
	};
}
#endif
