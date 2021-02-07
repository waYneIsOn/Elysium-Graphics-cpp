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
	class Game;

	class ELYSIUM_GRAPHICS_API GameTime final
	{
		friend class Game;
	public:
		GameTime(const GameTime& Source) = delete;
		GameTime(GameTime&& Right) noexcept = delete;
		~GameTime();

		GameTime& operator=(const GameTime& Source) = delete;
		GameTime& operator=(GameTime&& Right) noexcept = delete;

		// Returns the elapsed time since the last call to Game.Update(...).
		const Elysium::Core::TimeSpan& GetElapsedGameTime() const;

		// Returns the elapsed time since the start of the game.
		const Elysium::Core::TimeSpan& GetTotalGameTime() const;

		// Returns a value indicating whether the game is running slowly.
		const bool& GetIsRunningSlowly() const;
	private:
		GameTime();
		GameTime(const Elysium::Core::TimeSpan ElapsedGameTime, const Elysium::Core::TimeSpan TotalGameTime, const bool IsRunningSlowly);

		Elysium::Core::TimeSpan _ElapsedGameTime;
		Elysium::Core::TimeSpan _TotalGameTime;
		bool _IsRunningSlowly;
	};
}
#endif
