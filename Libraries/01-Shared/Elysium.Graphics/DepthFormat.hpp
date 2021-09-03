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
	/// <summary>
	/// 
	/// </summary>
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class DepthFormat : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class DepthFormat
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// 
		/// </summary>
		None,

		/// <summary>
		/// 
		/// </summary>
		Depth16,

		/// <summary>
		/// 
		/// </summary>
		Depth16Stencil8,

		/// <summary>
		/// 
		/// </summary>
		Depth24Stencil8,

		/// <summary>
		/// 
		/// </summary>
		Depth32,

		/// <summary>
		/// 
		/// </summary>
		Depth32Stencil8,
	};
}
#endif
