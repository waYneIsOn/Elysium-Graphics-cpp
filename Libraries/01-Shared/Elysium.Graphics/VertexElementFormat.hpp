/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VERTEXELEMENTFORMAT
#define ELYSIUM_GRAPHICS_RENDERING_VERTEXELEMENTFORMAT

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
	enum class VertexElementFormat : Elysium::Core::uint8_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class VertexElementFormat
#else
#error "undefined os"
#endif
	{
		Single = 0,

		Double = 1,

		Vector2Single = 2,

		Vector2Double = 3,

		Vector3Single = 4,

		Vector3Double = 5,

		Vector4Single = 6,

		Vector4Double = 7,

		Color = 8,

		Byte4 = 9,

		Short2 = 10,

		Short4 = 11,

		NormalizedShort2 = 12,

		NormalizedShort4 = 13,
	};
}
#endif
