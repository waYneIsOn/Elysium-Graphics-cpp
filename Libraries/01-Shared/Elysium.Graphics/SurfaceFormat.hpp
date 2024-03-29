/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_SURFACEFORMAT
#define ELYSIUM_GRAPHICS_RENDERING_SURFACEFORMAT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class SurfaceFormat : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class SurfaceFormat
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// Unspecified pixel format
		/// </summary>
		Undefined = 0,

		/// <summary>
		/// 32-bit BGRA pixel format stored with sRGB nonlinear
		/// </summary>
		B8G8R8A8_sRGB = 1,

		/// <summary>
		/// 32-bit RGBA pixel format stored with sRGB nonlinear
		/// </summary>
		R8G8B8A8_sRGB = 2,
	};
}
#endif
