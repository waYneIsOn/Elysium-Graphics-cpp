/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_COLORSPACEVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_COLORSPACEVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class ColorSpaceVk : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class ColorSpaceVk
#else
#error "undefined os"
#endif
	{
		SRGBNonLinear = 0,
		DisplayP3Nonlinear = 1000104001,
		ExtendedSRGBLinear = 1000104002,
		DisplayP3Linear = 1000104003,
		DCIP3NonLinear = 1000104004,
		BT709Linear = 1000104005,
		BT709NonLinear = 1000104006,
		BT2020Linear = 1000104007,
		HDR10ST2084 = 1000104008,
		DolbyVision = 1000104009,
		HDF10HLG = 1000104010,
		ADOBERGBLinear = 1000104011,
		ADOBERGBNonLinear = 1000104012,
		PassThrough = 1000104013,
		ExtendedSRGBNonLinear = 1000104014,
		DisplayNativeAMD = 1000213000,

		DisplayP3NonlinearExt = SRGBNonLinear,
		DCIP3Linear = DisplayP3Nonlinear,
	};
}
#endif
