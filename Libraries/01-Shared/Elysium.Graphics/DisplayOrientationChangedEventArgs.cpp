#include "DisplayOrientationChangedEventArgs.hpp"

Elysium::Graphics::Platform::DisplayOrientationChangedEventArgs::DisplayOrientationChangedEventArgs(const DisplayOrientation DisplayOrientation)
	: _DisplayOrientation(DisplayOrientation)
{ }
Elysium::Graphics::Platform::DisplayOrientationChangedEventArgs::~DisplayOrientationChangedEventArgs()
{ }

const Elysium::Graphics::Platform::DisplayOrientation& Elysium::Graphics::Platform::DisplayOrientationChangedEventArgs::GetDisplayOrientation() const
{
	return _DisplayOrientation;
}
