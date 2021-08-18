/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_INDEXELEMENTSIZE
#define ELYSIUM_GRAPHICS_RENDERING_INDEXELEMENTSIZE

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
	enum class IndexElementSize : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class IndexElementSize
#else
#error "undefined os"
#endif
	{
		SixteenBits = 16,

		ThirtyTwoBits = 32
	};
}
#endif
