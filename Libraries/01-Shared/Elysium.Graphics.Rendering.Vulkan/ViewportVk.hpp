/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_VIEWPORTVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_VIEWPORTVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEVIEWPORT
#include "../Elysium.Graphics/INativeViewport.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API ViewportVk final : public INativeViewport
	{
	public:
		ViewportVk(const Elysium::Core::uint32_t X, const Elysium::Core::uint32_t Y, const Elysium::Core::uint32_t Width,
			const Elysium::Core::uint32_t Height, const float MinimumDepth, const float MaximumDepth);
		ViewportVk(const ViewportVk& Source) = delete;
		ViewportVk(ViewportVk&& Right) noexcept = delete;
		virtual ~ViewportVk();

		ViewportVk& operator=(const ViewportVk& Source) = delete;
		ViewportVk& operator=(ViewportVk&& Right) noexcept = delete;
		
		virtual const float GetX() const override;
		virtual const float GetY() const override;
		virtual const float GetWidth() const override;
		virtual const float GetHeight() const override;
		virtual const float GetMinDepth() const override;
		virtual const float GetMaxDepth() const override;
	private:
		VkViewport _NativeViewport;
	};
}
#endif
