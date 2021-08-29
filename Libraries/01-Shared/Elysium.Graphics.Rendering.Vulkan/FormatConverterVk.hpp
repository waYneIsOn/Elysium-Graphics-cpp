/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FORMATCONVERTER
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_FORMATCONVERTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTMODE
#include "../Elysium.Graphics/PresentMode.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DEPTHFORMAT
#include "../Elysium.Graphics/DepthFormat.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_PHYSICALDEVICETYPE
#include "../Elysium.Graphics/PhysicalDeviceType.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_SURFACEFORMAT
#include "../Elysium.Graphics/SurfaceFormat.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class FormatConverterVk final
	{
	public:
		FormatConverterVk() = delete;
		FormatConverterVk(const FormatConverterVk& Source) = delete;
		FormatConverterVk(FormatConverterVk&& Right) noexcept = delete;
		~FormatConverterVk() = delete;

		FormatConverterVk& operator=(const FormatConverterVk& Source) = delete;
		FormatConverterVk& operator=(FormatConverterVk&& Right) noexcept = delete;

		static PhysicalDeviceType Convert(const VkPhysicalDeviceType Value);
		static VkPresentModeKHR Convert(const PresentMode Value);
		static VkFormat Convert(const SurfaceFormat Value);
		static VkFormat Convert(const DepthFormat Value);

		static SurfaceFormat Convert(const VkFormat Value);
		//static DepthFormat Convert(const VkFormat Value);
	};
}
#endif
