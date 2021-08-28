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

#ifndef ELYSIUM_GRAPHICS_PRESENTATIONPARAMETERS
#include "../Elysium.Graphics/PresentationParameters.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_DEVICEQUEUECREATEINFOVK
#include "DeviceQueueCreateInfoVk.hpp"
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

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API PresentationParametersVk final : public Elysium::Graphics::PresentationParameters
	{
		friend class GraphicsDeviceVk;
		friend class GraphicsInstanceVk;
		friend class GraphicsPipelineVk;
	public:
		PresentationParametersVk(GraphicsInstanceVk& NativeGraphicsAPI, Presentation::Control& Canvas);
		PresentationParametersVk(const PresentationParametersVk& Source) = delete;
		PresentationParametersVk(PresentationParametersVk&& Right) noexcept = delete;
		virtual ~PresentationParametersVk();

		PresentationParametersVk& operator=(const PresentationParametersVk& Source) = delete;
		PresentationParametersVk& operator=(PresentationParametersVk&& Right) noexcept = delete;

		void AddDeviceExtensionProperty(const ExtensionPropertyVk& ExtensionProperty);
		void ClearDeviceExtensionProperties();

		void AddDeviceQueueCreateInfo(DeviceQueueCreateInfoVk&& CreateInfo);
		void ClearDeviceQueueCreateInfo();
	private:
		// information required for creation of device and queues
		Core::Collections::Template::List<char*> _DeviceExtensionPropertyNames = Core::Collections::Template::List<char*>(0);
		Core::Collections::Template::List<DeviceQueueCreateInfoVk> _DeviceQueueCreateInfos = Core::Collections::Template::List<DeviceQueueCreateInfoVk>(0);
	};
}
#endif
