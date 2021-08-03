/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVERECTANGLE
#define ELYSIUM_GRAPHICS_RENDERING_INATIVERECTANGLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API INativeRectangle
	{
	public:
		virtual ~INativeRectangle() { }

		virtual const Elysium::Core::int32_t GetBottom() const = 0;
		virtual const Elysium::Core::int32_t GetLeft() const = 0;
		virtual const Elysium::Core::int32_t GetRight() const = 0;
		virtual const Elysium::Core::int32_t GetTop() const = 0;

		virtual const Elysium::Core::int32_t& GetX() const = 0;
		virtual const Elysium::Core::int32_t& GetY() const = 0;
		virtual const Elysium::Core::uint32_t& GetWidth() const = 0;
		virtual const Elysium::Core::uint32_t& GetHeight() const = 0;

		virtual void SetX(const Elysium::Core::int32_t Value) = 0;
		virtual void SetY(const Elysium::Core::int32_t Value) = 0;
		virtual void SetWidth(const Elysium::Core::int32_t Value) = 0;
		virtual void SetHeight(const Elysium::Core::int32_t Value) = 0;
	};
}
#endif
