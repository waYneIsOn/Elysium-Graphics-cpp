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
	/// <summary>
	/// 
	/// </summary>
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class ClearOptions : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class ClearOptions
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// 
		/// </summary>
		Target = 1,

		/// <summary>
		/// 
		/// </summary>
		DepthBuffer = 2,

		/// <summary>
		/// 
		/// </summary>
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
