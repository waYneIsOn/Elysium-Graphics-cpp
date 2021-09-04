/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_PRIMITIVETYPE
#define ELYSIUM_GRAPHICS_RENDERING_PRIMITIVETYPE

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
	/// Defines how vertex data is ordered.
	/// </summary>
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class PrimitiveType : Elysium::Core::uint8_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class PrimitiveType
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// The data is ordered as a sequence of triangles. Each triangle is described by three new vertices. Back-face culling is affected by the current winding-order render state.
		/// </summary>
		TriangleList = 0,

		/// <summary>
		/// The data is ordered as a sequence of triangles. Each triangle is described by two new vertices and one vertex from the previous triangle. The back-face culling flag is flipped automatically on even-numbered triangles.
		/// </summary>
		TriangleStrip = 1,

		/// <summary>
		/// The data is ordered as a sequence of line segments. Each line segment is described by two new vertices. The count may be any positive integer.
		/// </summary>
		LineList = 2,

		/// <summary>
		/// The data is ordered as a sequence of line segments. Each line segment is described by one new vertex and the last vertex from the previous line segment. The count may be any positive integer.
		/// </summary>
		LineStrip = 3,
	};
}
#endif
