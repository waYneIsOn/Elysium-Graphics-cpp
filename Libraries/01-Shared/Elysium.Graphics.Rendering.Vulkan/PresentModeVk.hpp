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
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class PresentModeVk : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class PresentModeVk
#else
#error "undefined os"
#endif
	{
		Immediate = 0,
		Mailbox = 1,
		Fifo = 2,
		FifoRelaxed = 3,
		SharedDemandRefresh = 1000111000,
		SharedContinuousRefresh = 1000111001
	};
}
#endif
