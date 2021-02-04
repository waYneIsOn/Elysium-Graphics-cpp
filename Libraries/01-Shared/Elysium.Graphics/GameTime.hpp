/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_GAMETIME
#define ELYSIUM_GRAPHICS_GAMETIME

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIME
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/DateTime.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/TimeSpan.hpp"
#endif

namespace Elysium::Graphics
{
	class ELYSIUM_GRAPHICS_API GameTime final
	{
	public:
		GameTime();
		GameTime(const GameTime& Source) = delete;
		GameTime(GameTime&& Right) noexcept = delete;
		~GameTime();

		GameTime& operator=(const GameTime& Source) = delete;
		GameTime& operator=(GameTime&& Right) noexcept = delete;
	};
}
#endif
