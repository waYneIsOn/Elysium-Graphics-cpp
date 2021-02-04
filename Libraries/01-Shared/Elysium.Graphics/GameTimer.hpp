/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_GAMETIMER
#define ELYSIUM_GRAPHICS_GAMETIMER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Graphics
{
	class ELYSIUM_GRAPHICS_API GameTimer final
	{
	public:
		GameTimer();
		GameTimer(const GameTimer& Source) = delete;
		GameTimer(GameTimer&& Right) noexcept = delete;
		~GameTimer();

		GameTimer& operator=(const GameTimer& Source) = delete;
		GameTimer& operator=(GameTimer&& Right) noexcept = delete;
	};
}
#endif
