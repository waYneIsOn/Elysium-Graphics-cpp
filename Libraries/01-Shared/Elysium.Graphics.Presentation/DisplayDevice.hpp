/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_PRESENTATION_DISPLAYDEVICE
#define ELYSIUM_GRAPHICS_PRESENTATION_DISPLAYDEVICE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_GEOMETRY_RECTANGLE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Math/Rectangle.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Vector.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATION_API
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

namespace Elysium::Graphics::Presentation
{
	class Window;

	class ELYSIUM_GRAPHICS_PRESENTATION_API DisplayDevice final
	{
		friend class Elysium::Core::Template::Container::Vector<Elysium::Graphics::Presentation::DisplayDevice>;
	private:
		DisplayDevice();

		DisplayDevice(const Elysium::Core::uint32_t Handle);

		DisplayDevice(DisplayDevice&& Right) noexcept;
	public:
		DisplayDevice(const DisplayDevice& Source) = delete;

		~DisplayDevice();
	public:
		DisplayDevice& operator=(const DisplayDevice& Source) = delete;
	private:
		DisplayDevice& operator=(DisplayDevice&& Right) noexcept;
	public:
		static const Elysium::Core::Template::Container::Vector<Elysium::Graphics::Presentation::DisplayDevice>& GetActiveDisplayDevices();

		static const Elysium::Graphics::Presentation::DisplayDevice& GetPrimaryDisplayDevice();

		static const Elysium::Graphics::Presentation::DisplayDevice& GetDisplayDeviceFromWindow(const Window& Window);
	public:
		const bool& GetIsPrimaryDisplayDevice() const;

		const Elysium::Core::Math::Geometry::Rectangle& GetCurrentBounds() const;
	private:
		Elysium::Core::uint32_t _DisplayDeviceHandle;
		bool _IsPrimaryDisplayDevice;
		Elysium::Core::Math::Geometry::Rectangle _CurrentBounds;
	private:
		void RefreshValues();
	private:
		static Elysium::Core::Template::Container::Vector<Elysium::Graphics::Presentation::DisplayDevice> _DisplayDevices;

		static Elysium::Core::Template::Container::Vector<Elysium::Graphics::Presentation::DisplayDevice> RetrieveDisplayDevices();

		static Elysium::Core::int32_t EnumDisplayDevicesCallback(HMONITOR Handle, HDC Dc, RECT* Rectangle, LPARAM Data);
	};
}
#endif
