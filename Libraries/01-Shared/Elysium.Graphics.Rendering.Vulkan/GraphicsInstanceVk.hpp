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

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSAPI
#include "../Elysium.Graphics/INativeGraphicsAPI.hpp"
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
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API GraphicsInstanceVk final : public INativeGraphicsAPI
	{
		friend class SurfaceVk;
	public:
		GraphicsInstanceVk();
		GraphicsInstanceVk(const GraphicsInstanceVk& Source) = delete;
		GraphicsInstanceVk(GraphicsInstanceVk&& Right) noexcept = delete;
		virtual ~GraphicsInstanceVk();

		GraphicsInstanceVk& operator=(const GraphicsInstanceVk& Source) = delete;
		GraphicsInstanceVk& operator=(GraphicsInstanceVk&& Right) noexcept = delete;

		static const Elysium::Core::Collections::Template::Array<ExtensionPropertyVk> GetAvailableExtensions();
		static const Elysium::Core::Collections::Template::Array<LayerPropertyVk> GetAvailableLayers();

		virtual const PhysicalDeviceVk& GetPhysicalDevice(const Elysium::Core::uint32_t Index) const override;
		//virtual const Elysium::Core::Collections::Template::Array<INativePhysicalDevice> GetPhysicalGraphicsDevices() const override;
		const Elysium::Core::Collections::Template::Array<PhysicalDeviceVk>& GetPhysicalGraphicsDevices();

		virtual void EnableDebugging() override;
		virtual void DisableDebugging() override;
	private:
		VkInstance _NativeInstanceHandle;
		VkDebugUtilsMessengerEXT _NativeDebugUtilsMessengerHandle;
		Elysium::Core::Collections::Template::Array<PhysicalDeviceVk> _PhysicalGraphicsDevices;

		VkInstance CreateInstance();
		Elysium::Core::Collections::Template::Array<PhysicalDeviceVk> RetrievePhysicalGraphicsDevices();
	private:
		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT MessageSeverity, VkDebugUtilsMessageTypeFlagsEXT MessageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
	};
}
#endif
