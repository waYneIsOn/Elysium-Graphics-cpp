/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICETYPEVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICETYPEVK

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
	enum class PhysicalDeviceTypeVk : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class PhysicalDeviceTypeVk
#else
#error "undefined os"
#endif
	{
		Other = 0,

		IntegratedGPU = 1,

		DiscreteGPU = 2,

		VirtualGPU = 3,

		CPU = 4,
	};
}
#endif
