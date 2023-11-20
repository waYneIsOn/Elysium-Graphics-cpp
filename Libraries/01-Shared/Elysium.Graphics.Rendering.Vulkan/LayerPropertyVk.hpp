/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_LAYERPROPERTYVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_LAYERPROPERTYVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"
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

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API LayerPropertyVk final
	{
		friend class GraphicsInstanceVk;
	public:
		LayerPropertyVk();

		LayerPropertyVk(const LayerPropertyVk& Source) = delete;

		LayerPropertyVk(LayerPropertyVk&& Right) noexcept = delete;

		~LayerPropertyVk();
	public:
		LayerPropertyVk& operator=(const LayerPropertyVk& Source) = delete;

		LayerPropertyVk& operator=(LayerPropertyVk&& Right) noexcept = delete;
	public:
		const Core::Utf8StringView GetName() const;

		const Core::uint32_t GetSpecVersion() const;

		const Core::uint32_t GetImplementationVersion() const;

		const Core::Utf8StringView GetDescription() const;
	private:
		VkLayerProperties _NativeProperty;
	};
}
#endif
