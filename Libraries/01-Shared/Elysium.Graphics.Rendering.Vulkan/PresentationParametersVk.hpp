/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PRESENTATIONPARAMETERSVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_PRESENTATIONPARAMETERSVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/List.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_PRESENTATIONPARAMETERS
#include "../Elysium.Graphics/PresentationParameters.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_DEVICEQUEUECREATEINFOVK
#include "DeviceQueueCreateInfoVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXTENT2DVK
#include "Extent2DVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXTENSIONPROPERTYVK
#include "ExtensionPropertyVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_LAYERPROPERTYVK
#include "LayerPropertyVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PRESENTMODEVK
#include "PresentModeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEVK
#include "SurfaceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SURFACEFORMATVK
#include "SurfaceFormatVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class GraphicsInstanceVk;
	class PhysicalDeviceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API PresentationParametersVk final : public PresentationParameters
	{
		friend class GraphicsInstanceVk;
		friend class PhysicalDeviceVk;
	public:
		PresentationParametersVk(Platform::Canvas& Canvas);
		PresentationParametersVk(const PresentationParametersVk& Source) = delete;
		PresentationParametersVk(PresentationParametersVk&& Right) noexcept = delete;
		virtual ~PresentationParametersVk();

		PresentationParametersVk& operator=(const PresentationParametersVk& Source) = delete;
		PresentationParametersVk& operator=(PresentationParametersVk&& Right) noexcept = delete;

		const Elysium::Core::String& GetApplicationName() const;
		const void* GetSurfaceHandle() const;
		const Elysium::Core::uint32_t GetGraphicsQueueFamilyIndex() const;
		const Elysium::Core::uint32_t GetPresentationQueueFamilyIndex() const;
		const Elysium::Core::uint32_t GetImageArrayLayers() const;
		const Elysium::Core::uint32_t GetTransform() const;
		const Extent2DVk& GetExtent() const;
		const SurfaceFormatVk& GetSurfaceFormat() const;
		const PresentModeVk& GetPresentMode() const;

		void SetApplicationName(const Elysium::Core::String& Value);
		void SetSurfaceHandle(const SurfaceVk& Value);
		void SetGraphicsQueueFamilyIndex(const Elysium::Core::uint32_t Value);
		void SetPresentationQueueFamilyIndex(const Elysium::Core::uint32_t Value);
		void SetImageArrayLayers(const Elysium::Core::uint32_t Value);
		void SetTransform(const Elysium::Core::uint32_t Value);
		void SetExtent(const Extent2DVk& Value);
		void SetSurfaceFormat(const SurfaceFormatVk& Value);
		void SetPresentMode(const PresentModeVk& Value);

		void AddInstanceExtensionProperty(const ExtensionPropertyVk& ExtensionProperty);
		void ClearInstanceExtensionProperties();

		void AddDeviceExtensionProperty(const ExtensionPropertyVk& ExtensionProperty);
		void ClearDeviceExtensionProperties();

		void AddLayerProperty(const LayerPropertyVk& LayerProperty);
		void ClearLayerProperties();

		void AddDeviceQueueCreateInfo(DeviceQueueCreateInfoVk&& CreateInfo);
		void ClearDeviceQueueCreateInfo();
	private:
		// information required for creation of instance
		Core::String _ApplicationName = u8"Elysium Graphics Application";
		Core::Collections::Template::List<char*> _InstanceExtensionPropertyNames = Core::Collections::Template::List<char*>(0);
		Core::Collections::Template::List<char*> _LayerPropertyNames = Core::Collections::Template::List<char*>(0);

		// information required for creation of device and queues
		void* _SurfaceHandle;
		Core::Collections::Template::List<char*> _DeviceExtensionPropertyNames = Core::Collections::Template::List<char*>(0);
		Elysium::Core::uint32_t _GraphicsQueueFamilyIndex = -1;
		Elysium::Core::uint32_t _PresentationQueueFamilyIndex = -1;
		Core::Collections::Template::List<DeviceQueueCreateInfoVk> _DeviceQueueCreateInfos = Core::Collections::Template::List<DeviceQueueCreateInfoVk>(0);

		// information required for creation of swapchain
		Elysium::Core::uint32_t _ImageArrayLayers = 1;
		Extent2DVk _Extent = Extent2DVk(_BackBufferWidth, _BackBufferHeight);
		SurfaceFormatVk _SurfaceFormat = SurfaceFormatVk();
		PresentModeVk _PresentMode = PresentModeVk();
		Elysium::Core::uint32_t _Transform = -1;
	};
}
#endif
