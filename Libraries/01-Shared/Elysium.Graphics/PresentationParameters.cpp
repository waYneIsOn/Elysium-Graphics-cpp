#include "PresentationParameters.hpp"

Elysium::Graphics::PresentationParameters::PresentationParameters()
	: _DisplayParameters()
{ }
Elysium::Graphics::PresentationParameters::~PresentationParameters()
{ }

const Elysium::Graphics::DisplayMode Elysium::Graphics::PresentationParameters::GetDisplayMode() const
{
	return _DisplayParameters._DisplayMode;
}

Elysium::Graphics::Platform::Canvas& Elysium::Graphics::PresentationParameters::GetCanvas() const
{
	return *_Canvas;
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
	_DisplayParameters._DisplayMode = Value;
}

void Elysium::Graphics::PresentationParameters::SetDisplayMonitor(Elysium::Graphics::Platform::IMonitor& Monitor)
{
	_DisplayParameters._SelectedMonitor = &Monitor;
}

void Elysium::Graphics::PresentationParameters::SetDisplayDevice(Elysium::Graphics::Rendering::INativePhysicalDevice& PhysicalDevice)
{
	_DisplayParameters._SelectedPhysicalDevice = &PhysicalDevice;
}

void Elysium::Graphics::PresentationParameters::SetCanvas(Platform::Canvas& Value)
{
	_Canvas = &Value;
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
