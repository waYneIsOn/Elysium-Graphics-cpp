/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXTENSIONPROPERTYVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXTENSIONPROPERTYVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/StringView.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class GraphicsInstanceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API ExtensionPropertyVk final
	{
		friend class GraphicsInstanceVk;
	public:
		ExtensionPropertyVk();
		ExtensionPropertyVk(const ExtensionPropertyVk& Source) = delete;
		ExtensionPropertyVk(ExtensionPropertyVk&& Right) noexcept = delete;
		~ExtensionPropertyVk();

		ExtensionPropertyVk& operator=(const ExtensionPropertyVk& Source) = delete;
		ExtensionPropertyVk& operator=(ExtensionPropertyVk&& Right) noexcept = delete;

		const Core::StringView GetName() const;
		const Core::uint32_t& GetSpecVersion() const;
	private:
		VkExtensionProperties _NativeProperty;
	};
}
#endif
