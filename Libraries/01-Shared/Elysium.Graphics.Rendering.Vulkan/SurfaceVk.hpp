/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_VULKAN_PRESENTMODEVK
#include "PresentModeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACECAPABILITIESVK
#include "SurfaceCapabilitiesVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEFORMATVK
#include "SurfaceFormatVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class GraphicsInstanceVk;
	class LogicalDeviceVk;
	class PhysicalDeviceVk;
	class QueueVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API SurfaceVk final
	{
		friend class GraphicsInstanceVk;
		friend class LogicalDeviceVk;
		friend class PhysicalDeviceVk;
		friend class QueueVk;
	public:
		SurfaceVk(const SurfaceVk& Source) = delete;
		SurfaceVk(SurfaceVk&& Right) noexcept = delete;
		~SurfaceVk();

		SurfaceVk& operator=(const SurfaceVk& Source) = delete;
		SurfaceVk& operator=(SurfaceVk&& Right) noexcept = delete;

		const SurfaceCapabilitiesVk GetCapabilities(const PhysicalDeviceVk& PhysicalDevice);
		const Elysium::Core::Collections::Template::Array<SurfaceFormatVk> GetFormats(const PhysicalDeviceVk& PhysicalDevice);
		const Elysium::Core::Collections::Template::Array<PresentModeVk> GetPresentModes(const PhysicalDeviceVk& PhysicalDevice);
	private:
		SurfaceVk(const VkInstance NativeInstanceHandle, const VkSurfaceKHR NativeSurfaceHandle);

		const VkInstance _NativeInstanceHandle;
		const VkSurfaceKHR _NativeSurfaceHandle;
	};
}
#endif
