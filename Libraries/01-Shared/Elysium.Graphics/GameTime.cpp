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

const bool& Elysium::Graphics::GameTime::GetIsUpdatingSlowly() const
{
	return _IsUpdatingSlowly;
}

Elysium::Graphics::GameTime::GameTime()
	: _ElapsedGameTime(0), _TotalGameTime(0), _Delta(0), _IsUpdatingSlowly(false)
{ }
