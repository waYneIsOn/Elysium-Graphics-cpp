#include "GameTimer.hpp"

Elysium::Graphics::GameTimer::GameTimer()
	: _Stopwatch(), _ElapsedTimeSpan(0), _LastElapsed(0)
{ 
	_Stopwatch.Start();
}
Elysium::Graphics::GameTimer::~GameTimer()
{
	_Stopwatch.Stop();
}

const Elysium::Core::TimeSpan& Elysium::Graphics::GameTimer::GetElapsedTimeSpan() const
{
	return _ElapsedTimeSpan;
}

void Elysium::Graphics::GameTimer::Update()
{
	Elysium::Core::TimeSpan Elapsed = _Stopwatch.GetElapsed();
	_ElapsedTimeSpan = Elapsed - _LastElapsed;
	_LastElapsed = Elapsed;
}
