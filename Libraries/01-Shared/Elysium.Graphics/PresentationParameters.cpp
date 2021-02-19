#include "PresentationParameters.hpp"

Elysium::Graphics::PresentationParameters::PresentationParameters(Rendering::INativeGraphicsAPI& NativeGraphicsAPI, Presentation::Control& Canvas)
	: _NativeGraphicsAPI(NativeGraphicsAPI), _Canvas(Canvas)
{ }
Elysium::Graphics::PresentationParameters::~PresentationParameters()
{ }

const Elysium::Graphics::DisplayMode Elysium::Graphics::PresentationParameters::GetDisplayMode() const
{
	return _DisplayMode;
}

const Elysium::Graphics::Presentation::Monitor& Elysium::Graphics::PresentationParameters::GetDisplayMonitor() const
{
	return Elysium::Graphics::Presentation::Monitor::GetActiveMonitors()[_MonitorIndex];
}
/*
const Elysium::Graphics::Rendering::INativePhysicalDevice& Elysium::Graphics::PresentationParameters::GetDisplayeDevice() const
{
	throw 1;
}
*/
Elysium::Graphics::Presentation::Control& Elysium::Graphics::PresentationParameters::GetCanvas() const
{
	return _Canvas;
}

const Elysium::Core::uint32_t Elysium::Graphics::PresentationParameters::GetBackBufferWidth() const
{
	return _BackBufferWidth;
}

const Elysium::Core::uint32_t Elysium::Graphics::PresentationParameters::GetBackBufferHeight() const
{
	return _BackBufferHeight;
}

const Elysium::Core::uint32_t Elysium::Graphics::PresentationParameters::GetBackBufferCount() const
{
	return _BackBufferCount;
}

void Elysium::Graphics::PresentationParameters::SetDisplayMode(const Elysium::Graphics::DisplayMode Value)
{
	_DisplayMode = Value;
}

void Elysium::Graphics::PresentationParameters::SetDisplayMonitorIndex(const Elysium::Core::uint32_t Value)
{
	_MonitorIndex = Value;
}

void Elysium::Graphics::PresentationParameters::SetDisplayDeviceIndex(const Elysium::Core::uint32_t Value)
{
	_PhysicalDeviceIndex = Value;
}

void Elysium::Graphics::PresentationParameters::SetBackBufferWidth(const Elysium::Core::uint32_t Value)
{
	_BackBufferWidth = Value;
}

void Elysium::Graphics::PresentationParameters::SetBackBufferHeight(const Elysium::Core::uint32_t Value)
{
	_BackBufferHeight = Value;
}

void Elysium::Graphics::PresentationParameters::SetBackBufferCount(const Elysium::Core::uint32_t Value)
{
	_BackBufferCount = Value;
}
