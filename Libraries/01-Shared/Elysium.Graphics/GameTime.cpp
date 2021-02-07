#include "GameTime.hpp"

Elysium::Graphics::GameTime::~GameTime()
{ }

const Elysium::Core::TimeSpan& Elysium::Graphics::GameTime::GetElapsedGameTime() const
{
	return _ElapsedGameTime;
}

const Elysium::Core::TimeSpan& Elysium::Graphics::GameTime::GetTotalGameTime() const
{
	return _TotalGameTime;
}

const bool& Elysium::Graphics::GameTime::GetIsRunningSlowly() const
{
	return _IsRunningSlowly;
}

Elysium::Graphics::GameTime::GameTime()
	: _ElapsedGameTime(0), _TotalGameTime(0), _IsRunningSlowly(false)
{ }

Elysium::Graphics::GameTime::GameTime(const Elysium::Core::TimeSpan ElapsedGameTime, const Elysium::Core::TimeSpan TotalGameTime, const bool IsRunningSlowly)
	: _ElapsedGameTime(ElapsedGameTime), _TotalGameTime(TotalGameTime), _IsRunningSlowly(IsRunningSlowly)
{ }
