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

		const Elysium::Core::Collections::Template::Array<ExtensionPropertyVk> GetAvailableExtensions();
		const Elysium::Core::Collections::Template::Array<LayerPropertyVk> GetAvailableLayers();

		const Elysium::Core::Collections::Template::Array<PhysicalDeviceVk> GetPhysicalGraphicsDevices();

		void SetApplicationName(const Elysium::Core::String& Value);
		void AddInstanceExtensionProperty(const ExtensionPropertyVk& ExtensionProperty);
		void ClearInstanceExtensionProperties();

		void AddLayerProperty(const LayerPropertyVk& LayerProperty);
		void ClearLayerProperties();

		virtual void EnableDebugging() override;
		virtual void DisableDebugging() override;

		virtual void Initialize() override;
	private:
		Elysium::Core::String _ApplicationName = u8"Elysium Graphics Application";
		Elysium::Core::Collections::Template::List<char*> _InstanceExtensionPropertyNames = Elysium::Core::Collections::Template::List<char*>(0);
		Elysium::Core::Collections::Template::List<char*> _LayerPropertyNames = Elysium::Core::Collections::Template::List<char*>(0);

		VkInstance _NativeInstanceHandle = VK_NULL_HANDLE;
		VkDebugUtilsMessengerEXT _NativeDebugUtilsMessengerHandle = VK_NULL_HANDLE;

		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT MessageSeverity, VkDebugUtilsMessageTypeFlagsEXT MessageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
	};
}
#endif
