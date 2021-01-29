/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_PLATFORM_IGAMEWINDOW
#define ELYSIUM_GRAPHICS_PLATFORM_IGAMEWINDOW

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Platform
{
	class ELYSIUM_GRAPHICS_API IGameWindow
	{
	public:
		virtual ~IGameWindow() { }

		virtual void Show() = 0;
		virtual void Close() = 0;
	};
}
#endif
