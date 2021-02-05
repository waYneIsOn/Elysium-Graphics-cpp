/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SWAPCHAINCREATEINFOVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_SWAPCHAINCREATEINFOVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXTENT2DVK
#include "Extent2DVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PRESENTMODEVK
#include "PresentModeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEFORMATVK
#include "SurfaceFormatVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API SwapchainCreateInfoVk final
	{
	public:
		SwapchainCreateInfoVk();
		SwapchainCreateInfoVk(const SwapchainCreateInfoVk& Source) = delete;
		SwapchainCreateInfoVk(SwapchainCreateInfoVk&& Right) noexcept = delete;
		~SwapchainCreateInfoVk();

		SwapchainCreateInfoVk& operator=(const SwapchainCreateInfoVk& Source) = delete;
		SwapchainCreateInfoVk& operator=(SwapchainCreateInfoVk&& Right) noexcept = delete;

		Elysium::Core::uint32_t GraphicsFamilyIndex = -1;
		Elysium::Core::uint32_t PresentFamilyIndex = -1;
		Elysium::Core::uint32_t NumberOfImages = -1;
		Elysium::Core::uint32_t ImageArrayLayers = 1;	// ToDo: 2 would be 3d camera with left and right eye
		Extent2DVk Extend = Extent2DVk(0, 0);
		SurfaceFormatVk SurfaceFormat = SurfaceFormatVk();
		PresentModeVk PresentMode = PresentModeVk();
		Elysium::Core::uint32_t Transform = -1;
	};
}
#endif
