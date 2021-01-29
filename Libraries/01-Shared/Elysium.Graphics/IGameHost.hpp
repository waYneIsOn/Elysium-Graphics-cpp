/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_PLATFORM_IGAMEHOST
#define ELYSIUM_GRAPHICS_PLATFORM_IGAMEHOST

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PLATFORM_IGAMEWINDOW
#include "IGameWindow.hpp"
#endif

namespace Elysium::Graphics::Platform
{
	class ELYSIUM_GRAPHICS_API IGameHost
	{
	public:
		virtual ~IGameHost() { }

		virtual const IGameWindow& GetGameWindow() const = 0;

		virtual void Run() = 0;
		virtual void Exit() = 0;
	};
}
#endif
