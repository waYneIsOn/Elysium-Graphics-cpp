/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PRESENTMODEVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_PRESENTMODEVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	/// <summary>
	/// 
	/// </summary>
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class PresentModeVk : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class PresentModeVk
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// 
		/// </summary>
		Immediate = 0,

		/// <summary>
		/// 
		/// </summary>
		Mailbox = 1,

		/// <summary>
		/// 
		/// </summary>
		Fifo = 2,

		/// <summary>
		/// 
		/// </summary>
		FifoRelaxed = 3,

		/// <summary>
		/// 
		/// </summary>
		SharedDemandRefresh = 1000111000,

		/// <summary>
		/// 
		/// </summary>
		SharedContinuousRefresh = 1000111001
	};
}
#endif
