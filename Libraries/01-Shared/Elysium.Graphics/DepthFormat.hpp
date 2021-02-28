/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_DEPTHFORMAT
#define ELYSIUM_GRAPHICS_RENDERING_DEPTHFORMAT

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
	enum class DepthFormat : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class DepthFormat
#else
#error "undefined os"
#endif
	{
		None,

		Depth16,

		Depth16Stencil8,

		Depth24Stencil8,

		Depth32,

		Depth32Stencil8,
	};
}
#endif
