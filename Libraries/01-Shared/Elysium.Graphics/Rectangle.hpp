/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_RECTANGLE
#define ELYSIUM_GRAPHICS_RENDERING_RECTANGLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVERECTANGLE
#include "INativeRectangle.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API Rectangle final
	{
	public:
		Rectangle(const Rectangle& Source) = delete;
		Rectangle(Rectangle&& Right) noexcept = delete;
		~Rectangle();

		Rectangle& operator=(const Rectangle& Source) = delete;
		Rectangle& operator=(Rectangle&& Right) noexcept = delete;

		const Elysium::Core::int32_t GetBottom() const;
		const Elysium::Core::int32_t GetLeft() const;
		const Elysium::Core::int32_t GetRight() const;
		const Elysium::Core::int32_t GetTop() const;

		const Elysium::Core::int32_t& GetX() const;
		const Elysium::Core::int32_t& GetY() const;
		const Elysium::Core::uint32_t& GetWidth() const;
		const Elysium::Core::uint32_t& GetHeight() const;

		void SetX(const Elysium::Core::int32_t Value);
		void SetY(const Elysium::Core::int32_t Value);
		void SetWidth(const Elysium::Core::int32_t Value);
		void SetHeight(const Elysium::Core::int32_t Value);
	private:
		Rectangle(INativeRectangle& NativeRectangle);

		INativeRectangle& _NativeRectangle;
	};
}
#endif
