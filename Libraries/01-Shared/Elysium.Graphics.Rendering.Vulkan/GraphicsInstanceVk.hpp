/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSINSTANCEVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSINSTANCEVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXTENSIONPROPERTYVK
#include "ExtensionPropertyVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_LAYERPROPERTYVK
#include "LayerPropertyVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICEVK
#include "PhysicalDeviceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PRESENTATIONPARAMETERSVK
#include "PresentationParametersVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEVK
#include "SurfaceVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API GraphicsInstanceVk final
	{
	public:
		GraphicsInstanceVk();
		GraphicsInstanceVk(const GraphicsInstanceVk& Source) = delete;
		GraphicsInstanceVk(GraphicsInstanceVk&& Right) noexcept = delete;
		~GraphicsInstanceVk();

		GraphicsInstanceVk& operator=(const GraphicsInstanceVk& Source) = delete;
		GraphicsInstanceVk& operator=(GraphicsInstanceVk&& Right) noexcept = delete;

		const Elysium::Core::Collections::Template::Array<ExtensionPropertyVk> GetAvailableExtensions();
		const Elysium::Core::Collections::Template::Array<LayerPropertyVk> GetAvailableLayers();

		const Elysium::Core::Collections::Template::Array<PhysicalDeviceVk> GetPhysicalGraphicsDevices();

		void Initialize(const PresentationParametersVk& PresentationParameters);
		SurfaceVk CreateSurface(const PresentationParametersVk& PresentationParameters);
	private:
		VkInstance _NativeInstanceHandle = VK_NULL_HANDLE;
	};
}
#endif
