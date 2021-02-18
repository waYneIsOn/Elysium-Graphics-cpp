/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_DISPLAYORIENTATIONCHANGEDEVENTARGS
#define ELYSIUM_GRAPHICS_DISPLAYORIENTATIONCHANGEDEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EVENTARGS
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/EventArgs.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_DISPLAYORIENTATION
#include "DisplayOrientation.hpp"
#endif

namespace Elysium::Graphics::Platform
{
	class ELYSIUM_GRAPHICS_API DisplayOrientationChangedEventArgs : public Core::EventArgs
	{
	public:
		DisplayOrientationChangedEventArgs(const Elysium::Graphics::DisplayOrientation DisplayOrientation);
		DisplayOrientationChangedEventArgs(const DisplayOrientationChangedEventArgs& Source) = delete;
		DisplayOrientationChangedEventArgs(DisplayOrientationChangedEventArgs&& Right) noexcept = delete;
		virtual ~DisplayOrientationChangedEventArgs();

		DisplayOrientationChangedEventArgs& operator=(const DisplayOrientationChangedEventArgs& Source) = delete;
		DisplayOrientationChangedEventArgs& operator=(DisplayOrientationChangedEventArgs&& Right) noexcept = delete;

		const Elysium::Graphics::DisplayOrientation& GetDisplayOrientation() const;
	private:
		const Elysium::Graphics::DisplayOrientation _DisplayOrientation;
	};
}
#endif
