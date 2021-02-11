/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_PLATFORM_SIZECHANGEDEVENTARGS
#define ELYSIUM_GRAPHICS_PLATFORM_SIZECHANGEDEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EVENTARGS
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/EventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Platform
{
	class ELYSIUM_GRAPHICS_API SizeChangedEventArgs : public Core::EventArgs
	{
	public:
		SizeChangedEventArgs(const Elysium::Core::uint32_t Width, const Elysium::Core::uint32_t Height);
		SizeChangedEventArgs(const SizeChangedEventArgs& Source) = delete;
		SizeChangedEventArgs(SizeChangedEventArgs&& Right) noexcept = delete;
		virtual ~SizeChangedEventArgs();

		SizeChangedEventArgs& operator=(const SizeChangedEventArgs& Source) = delete;
		SizeChangedEventArgs& operator=(SizeChangedEventArgs&& Right) noexcept = delete;

		const Elysium::Core::uint32_t& GetWidth() const;
		const Elysium::Core::uint32_t& GetHeight() const;
	private:
		const Elysium::Core::uint32_t _Width;
		const Elysium::Core::uint32_t _Height;
	};
}
#endif
