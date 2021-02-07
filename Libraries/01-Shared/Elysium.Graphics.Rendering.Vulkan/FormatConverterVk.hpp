/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_DEVICEQUEUECREATEINFOVK

#ifdef _MSC_VER
#pragma once
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

		static const VkFormat Convert(const SurfaceFormat& Format);
	};
}
#endif
