/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VERTEXELEMENTUSAGE
#define ELYSIUM_GRAPHICS_RENDERING_VERTEXELEMENTUSAGE

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
	enum class VertexElementUsage : Elysium::Core::uint8_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class VertexElementUsage
#else
#error "undefined os"
#endif
	{
		Position = 0,

		Color = 1,

		TextureCoordinate = 2,

		Normal = 3,
		/*
		Binormal = 4,

		Tangent = 5,

		BlendIndices = 6,

		BlendWeight = 7,

		Depth = 8,

		Fog = 9,

		PointSize = 10,

		Sample = 11,

		TessellateFactor = 12
		*/
	};
}
#endif
