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

#ifndef ELYSIUM_GRAPHICS_PRESENTATION_CONTROL
#include "../Elysium.Graphics.Presentation/Control.hpp"
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

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEFORMATVK
#include "SurfaceFormatVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class GraphicsInstanceVk;
	class GraphicsDeviceVk;
	class LogicalDeviceVk;
	class PhysicalDeviceVk;
	class PresentationParametersVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API SurfaceVk final
	{
		friend class GraphicsDeviceVk;
		friend class LogicalDeviceVk;
		friend class PhysicalDeviceVk;
		friend class PresentationParametersVk;
		friend class QueueVk;
		friend class SwapchainVk;
	public:
		SurfaceVk(const GraphicsInstanceVk& GraphicsInstance, const PhysicalDeviceVk& PhysicalDevice, PresentationParametersVk& PresentationParameters);
		SurfaceVk(const SurfaceVk& Source) = delete;
		SurfaceVk(SurfaceVk&& Right) noexcept = delete;
		~SurfaceVk();

		SurfaceVk& operator=(const SurfaceVk& Source) = delete;
		SurfaceVk& operator=(SurfaceVk&& Right) noexcept = delete;

		Elysium::Core::Event<void, const SurfaceVk&> SizeChanged;
	private:
		const VkInstance _NativeInstanceHandle;
		const PhysicalDeviceVk& _PhysicalDevice;
		PresentationParametersVk& _PresentationParameters;
		Elysium::Graphics::Presentation::Control& _Canvas;

		const VkSurfaceKHR _NativeSurfaceHandle;
		VkSurfaceCapabilitiesKHR _NativeSurfaceCapabilities;

		const VkSurfaceKHR CreateNativeSurface();
		VkSurfaceCapabilitiesKHR GetNativeSurfaceCapabilities();

		void UpdateInternalValues();

		void Control_SizeChanged(const Elysium::Graphics::Presentation::Control& Sender, const Elysium::Core::int32_t Width, const Elysium::Core::int32_t Height);
	};
}
#endif
