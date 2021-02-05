/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACECAPABILITIESVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACECAPABILITIESVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXTENT2DVK
#include "Extent2DVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class SurfaceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API SurfaceCapabilitiesVk final
	{
		friend class SurfaceVk;
	public:
		SurfaceCapabilitiesVk(const SurfaceCapabilitiesVk& Source) = delete;
		SurfaceCapabilitiesVk(SurfaceCapabilitiesVk&& Right) noexcept = delete;
		~SurfaceCapabilitiesVk();

		SurfaceCapabilitiesVk& operator=(const SurfaceCapabilitiesVk& Source) = delete;
		SurfaceCapabilitiesVk& operator=(SurfaceCapabilitiesVk&& Right) noexcept = delete;

		const Elysium::Core::uint32_t GetMinImageCount() const;
		const Elysium::Core::uint32_t GetMaxImageCount() const;
		const Extent2DVk GetCurrentExtent() const;
		const Extent2DVk GetMinImageExtent() const;
		const Extent2DVk GetMaxImageExtent() const;
		const Elysium::Core::uint32_t GetMaxImageArrayLayers() const;
		const Elysium::Core::uint32_t GetSupportedTransforms() const;
		const Elysium::Core::uint32_t GetCurrentTransform() const;
		const Elysium::Core::uint32_t GetSupportedCompositeAlpha() const;
		const Elysium::Core::uint32_t GetSupportedUsageFlags() const;
	private:
		SurfaceCapabilitiesVk(const VkSurfaceCapabilitiesKHR NativeSurfaceCapabilities);

		const VkSurfaceCapabilitiesKHR _NativeSurfaceCapabilities;
	};
}
#endif
