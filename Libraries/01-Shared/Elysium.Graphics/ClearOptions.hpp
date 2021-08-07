/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_CLEAROPTIONS
#define ELYSIUM_GRAPHICS_RENDERING_CLEAROPTIONS

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
	enum class ClearOptions : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class ClearOptions
#else
#error "undefined os"
#endif
	{
		Target = 1,
		DepthBuffer = 2,
		Stencil = 4,
	};

	inline ClearOptions operator|(const ClearOptions Left, const ClearOptions Right)
	{
		return static_cast<ClearOptions>(static_cast<Elysium::Core::uint32_t>(Left) | static_cast<Elysium::Core::uint32_t>(Right));
	}
	inline ClearOptions operator&(const ClearOptions Left, const ClearOptions Right)
	{
		return static_cast<ClearOptions>(static_cast<Elysium::Core::uint32_t>(Left) & static_cast<Elysium::Core::uint32_t>(Right));
	}
}
#endif
