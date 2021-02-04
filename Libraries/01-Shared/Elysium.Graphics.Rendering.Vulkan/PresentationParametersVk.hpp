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

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXTENSIONPROPERTYVK
#include "ExtensionPropertyVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_LAYERPROPERTYVK
#include "LayerPropertyVk.hpp"
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
		PresentationParametersVk(const Platform::Canvas& Canvas);
		PresentationParametersVk(const PresentationParametersVk& Source) = delete;
		PresentationParametersVk(PresentationParametersVk&& Right) noexcept = delete;
		virtual ~PresentationParametersVk();

		PresentationParametersVk& operator=(const PresentationParametersVk& Source) = delete;
		PresentationParametersVk& operator=(PresentationParametersVk&& Right) noexcept = delete;

		const Core::String& GetApplicationName() const;

		void AddExtensionProperty(const ExtensionPropertyVk& ExtensionProperty);
		void ClearExtensionProperties();

		void AddLayerProperty(const LayerPropertyVk& LayerProperty);
		void ClearLayerProperties();

		virtual void Bla() override
		{ }
	private:
		Core::String _ApplicationName = u8"Elysium Graphics Application";
		Core::Collections::Template::List<char*> _ExtensionPropertyNames = Core::Collections::Template::List<char*>(0);
		Core::Collections::Template::List<char*> _LayerPropertyNames = Core::Collections::Template::List<char*>(0);
	};
}
#endif
