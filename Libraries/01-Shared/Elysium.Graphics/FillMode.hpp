/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_FILLMODE
#define ELYSIUM_GRAPHICS_RENDERING_FILLMODE

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
	/// <summary>
	/// Describes options for filling the vertices and lines that define a primitive.
	/// </summary>
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class FillMode : Elysium::Core::uint8_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class FillMode
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// ... solid
		/// </summary>
		Fill = 0,

		/// <summary>
		/// ... wireframe
		/// </summary>
		Line = 1,

		/// <summary>
		/// 
		/// </summary>
		Point = 2,
	};
}
#endif
