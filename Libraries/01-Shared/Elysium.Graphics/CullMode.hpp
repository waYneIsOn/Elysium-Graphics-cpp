/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_CULLMODE
#define ELYSIUM_GRAPHICS_RENDERING_CULLMODE

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
	/// Defines winding orders that may be used to identify back faces for culling.
	/// </summary>
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class CullMode : Elysium::Core::uint8_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class CullMode
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// Do not cull back faces.
		/// </summary>
		None = 0,

		/// <summary>
		/// Cull back faces with clockwise vertices.
		/// </summary>
		CullClockwiseFace = 1,

		/// <summary>
		/// Cull back faces with counterclockwise vertices.
		/// </summary>
		CullCounterClockwiseFace = 2,
	};
}
#endif
