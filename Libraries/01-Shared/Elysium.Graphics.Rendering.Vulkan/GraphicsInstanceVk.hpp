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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Vector.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSAPI
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

namespace Elysium::Graphics::Rendering::Vulkan
{
	/// <summary>
	/// 
	/// </summary>
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API GraphicsInstanceVk final : public Native::INativeGraphicsAPI
	{
		friend class GraphicsDeviceVk;
	public:
		GraphicsInstanceVk();

		GraphicsInstanceVk(const GraphicsInstanceVk& Source) = delete;

		GraphicsInstanceVk(GraphicsInstanceVk&& Right) noexcept = delete;

		virtual ~GraphicsInstanceVk();
	public:
		GraphicsInstanceVk& operator=(const GraphicsInstanceVk& Source) = delete;

		GraphicsInstanceVk& operator=(GraphicsInstanceVk&& Right) noexcept = delete;
	public:
		const Elysium::Core::Template::Container::Vector<ExtensionPropertyVk> GetAvailableExtensions();

		const Elysium::Core::Template::Container::Vector<LayerPropertyVk> GetAvailableLayers();

		virtual const PhysicalDeviceVk& GetPhysicalDevice(const Elysium::Core::uint32_t Index) const override;
		//virtual const Elysium::Core::Template::Container::Vector<INativePhysicalDevice> GetPhysicalGraphicsDevices() const override;
		const Elysium::Core::Template::Container::Vector<PhysicalDeviceVk>& GetPhysicalDevices();
	public:
		virtual void EnableDebugging() override;

		virtual void DisableDebugging() override;
	private:
		VkInstance CreateInstance();

		Elysium::Core::Template::Container::Vector<PhysicalDeviceVk> RetrievePhysicalDevices();
	private:
		VkInstance _NativeInstanceHandle;
		VkDebugUtilsMessengerEXT _NativeDebugUtilsMessengerHandle;
		Elysium::Core::Template::Container::Vector<PhysicalDeviceVk> _PhysicalDevices;
	private:
		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT MessageSeverity, VkDebugUtilsMessageTypeFlagsEXT MessageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
	};
}
#endif
