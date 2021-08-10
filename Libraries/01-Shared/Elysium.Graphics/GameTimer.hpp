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

#ifndef ELYSIUM_CORE_TIMESPAN
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/TimeSpan.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_STOPWATCH
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Diagnostics/Stopwatch.hpp"
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

		const Elysium::Core::TimeSpan& GetElapsedTimeSpan() const;

		void Update();
	private:
		Elysium::Core::Diagnostics::Stopwatch _Stopwatch;
		Elysium::Core::TimeSpan _ElapsedTimeSpan;
		Elysium::Core::TimeSpan _LastElapsed;
	};
}
#endif
