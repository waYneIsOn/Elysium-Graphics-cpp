/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_PLATFORM_DISPLAYORIENTATIONCHANGEDEVENTARGS
#define ELYSIUM_GRAPHICS_PLATFORM_DISPLAYORIENTATIONCHANGEDEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EVENTARGS
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/EventArgs.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PLATFORM_DISPLAYORIENTATION
#include "DisplayOrientation.hpp"
#endif

namespace Elysium::Graphics::Platform
{
	class ELYSIUM_GRAPHICS_API DisplayOrientationChangedEventArgs : public Core::EventArgs
	{
	public:
		DisplayOrientationChangedEventArgs(const DisplayOrientation DisplayOrientation);
		DisplayOrientationChangedEventArgs(const DisplayOrientationChangedEventArgs& Source) = delete;
		DisplayOrientationChangedEventArgs(DisplayOrientationChangedEventArgs&& Right) noexcept = delete;
		virtual ~DisplayOrientationChangedEventArgs();

		DisplayOrientationChangedEventArgs& operator=(const DisplayOrientationChangedEventArgs& Source) = delete;
		DisplayOrientationChangedEventArgs& operator=(DisplayOrientationChangedEventArgs&& Right) noexcept = delete;

		const DisplayOrientation& GetDisplayOrientation() const;
	private:
		const DisplayOrientation _DisplayOrientation;
	};
}
#endif
