/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_PLATFORM_MONITOR
#define ELYSIUM_GRAPHICS_PLATFORM_MONITOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/List.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_GEOMETRY_RECTANGLE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Math/Rectangle.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)
#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef _WINGDI_
#include <wingdi.h>
#endif
#elif defined(ELYSIUM_CORE_OS_ANDROID)
#error "unsupported os"
#elif defined(ELYSIUM_CORE_OS_LINUX)
#error "unsupported os"
#elif defined(ELYSIUM_CORE_OS_MAC)
#error "unsupported os"
#else
#error "unsupported os"
#endif

namespace Elysium::Graphics::Platform
{
	class ELYSIUM_GRAPHICS_API Monitor final
	{
		friend class Elysium::Core::Collections::Template::List<Elysium::Graphics::Platform::Monitor>;
	public:
		Monitor(const Monitor& Source) = delete;
		~Monitor();

		Monitor& operator=(const Monitor& Source) = delete;

		static const Elysium::Core::Collections::Template::List<Elysium::Graphics::Platform::Monitor>& GetActiveMonitors();
		static const Elysium::Graphics::Platform::Monitor& GetPrimaryMonitor();

		const bool& GetIsPrimaryMonitor() const;

		void Test() {}
	private:
		Elysium::Core::uint32_t _Handle;
		bool _IsPrimaryMonitor;
		Elysium::Core::Math::Geometry::Rectangle _CurrentBounds;

		Monitor();
		Monitor(const Elysium::Core::uint32_t Handle);
		Monitor(Monitor&& Right) noexcept;

		Monitor& operator=(Monitor&& Right) noexcept;

		void RefreshValues();
	private:
		static Elysium::Core::Collections::Template::List<Elysium::Graphics::Platform::Monitor> _Monitors;

		static Elysium::Core::int32_t EnumDisplayMonitorsCallback(HMONITOR Handle, HDC Dc, RECT* Rectangle, LPARAM Data);
	};
}
#endif
