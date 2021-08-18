/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEFORMATVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEFORMATVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FORMATVK
#include "FormatVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_COLORSPACEVK
#include "ColorSpaceVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API SurfaceFormatVk final
	{
	public:
		SurfaceFormatVk();
		SurfaceFormatVk(const SurfaceFormatVk& Source) = delete;
		SurfaceFormatVk(SurfaceFormatVk&& Right) noexcept = delete;
		~SurfaceFormatVk();

		SurfaceFormatVk& operator=(const SurfaceFormatVk& Source) = delete;
		SurfaceFormatVk& operator=(SurfaceFormatVk&& Right) noexcept = delete;
		
		FormatVk Format;
		ColorSpaceVk ColorSpace;
	};
}
#endif
