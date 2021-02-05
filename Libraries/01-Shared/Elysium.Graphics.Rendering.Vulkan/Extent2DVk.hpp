/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXTENT2DVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXTENT2DVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API Extent2DVk final
	{
	public:
		Extent2DVk();
		Extent2DVk(Elysium::Core::uint32_t Width, Elysium::Core::uint32_t Height);
		Extent2DVk(const Extent2DVk& Source);
		Extent2DVk(Extent2DVk&& Right) noexcept;
		~Extent2DVk();

		Extent2DVk& operator=(const Extent2DVk& Source);
		Extent2DVk& operator=(Extent2DVk&& Right) noexcept;

		Elysium::Core::uint32_t Width;
		Elysium::Core::uint32_t Height;
	};
}
#endif
