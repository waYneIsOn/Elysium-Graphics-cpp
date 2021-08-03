/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_RECTANGLEVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_RECTANGLEVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVERECTANGLE
#include "../Elysium.Graphics/INativeRectangle.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API RectangleVk final : public INativeRectangle
	{
	public:
		RectangleVk(const Elysium::Core::int32_t X, const Elysium::Core::int32_t Y, const Elysium::Core::uint32_t Width, const Elysium::Core::uint32_t Height);
		RectangleVk(const RectangleVk& Source) = delete;
		RectangleVk(RectangleVk&& Right) noexcept = delete;
		virtual ~RectangleVk();

		RectangleVk& operator=(const RectangleVk& Source) = delete;
		RectangleVk& operator=(RectangleVk&& Right) noexcept = delete;

		virtual const Elysium::Core::int32_t GetBottom() const override;
		virtual const Elysium::Core::int32_t GetLeft() const override;
		virtual const Elysium::Core::int32_t GetRight() const override;
		virtual const Elysium::Core::int32_t GetTop() const override;

		virtual const Elysium::Core::int32_t& GetX() const override;
		virtual const Elysium::Core::int32_t& GetY() const override;
		virtual const Elysium::Core::uint32_t& GetWidth() const override;
		virtual const Elysium::Core::uint32_t& GetHeight() const override;

		virtual void SetX(const Elysium::Core::int32_t Value) override;
		virtual void SetY(const Elysium::Core::int32_t Value) override;
		virtual void SetWidth(const Elysium::Core::int32_t Value) override;
		virtual void SetHeight(const Elysium::Core::int32_t Value) override;
	private:
		VkRect2D _NativeRectangle;
	};
}
#endif
