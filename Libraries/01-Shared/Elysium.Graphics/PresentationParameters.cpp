#include "PresentationParameters.hpp"

Elysium::Graphics::PresentationParameters::PresentationParameters(Rendering::Native::INativeGraphicsAPI& NativeGraphicsAPI, Presentation::Control& Canvas)
	: _NativeGraphicsAPI(NativeGraphicsAPI), _Canvas(Canvas)
{ }

Elysium::Graphics::PresentationParameters::~PresentationParameters()
{ }

const Elysium::Graphics::DisplayMode Elysium::Graphics::PresentationParameters::GetDisplayMode() const
{
	return _DisplayMode;
}

const Elysium::Graphics::Presentation::DisplayDevice& Elysium::Graphics::PresentationParameters::GetDisplayDevice() const
{
	return Elysium::Graphics::Presentation::DisplayDevice::GetActiveDisplayDevices()[_DisplayDeviceIndex];
}

const Elysium::Graphics::Rendering::Native::INativePhysicalDevice& Elysium::Graphics::PresentationParameters::GetPhysicalDevice() const
{
	return _NativeGraphicsAPI.GetPhysicalDevice(_GraphicsDeviceIndex);
}

Elysium::Graphics::Presentation::Control& Elysium::Graphics::PresentationParameters::GetCanvas() const
{
	return _Canvas;
}

const Elysium::Core::uint32_t Elysium::Graphics::PresentationParameters::GetRenderResolution() const
{
	return _RenderResolution;
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

const Elysium::Graphics::PresentMode Elysium::Graphics::PresentationParameters::GetPresentMode() const
{
	return _PresentMode;
}

const Elysium::Graphics::Rendering::SurfaceFormat Elysium::Graphics::PresentationParameters::GetDesiredSurfaceFormat() const
{
	return _DesiredSurfaceFormat;
}

const Elysium::Graphics::Rendering::DepthFormat Elysium::Graphics::PresentationParameters::GetDesiredDepthStencilFormat() const
{
	return _DesiredDepthStencilFormat;
}

void Elysium::Graphics::PresentationParameters::SetDisplayMode(const Elysium::Graphics::DisplayMode Value)
{
	_DisplayMode = Value;
}

void Elysium::Graphics::PresentationParameters::SetDisplayDeviceIndex(const Elysium::Core::uint32_t Value)
{
	_DisplayDeviceIndex = Value;
}

void Elysium::Graphics::PresentationParameters::SetGraphicsDeviceIndex(const Elysium::Core::uint32_t Value)
{
	_GraphicsDeviceIndex = Value;
}

void Elysium::Graphics::PresentationParameters::SetPresentMode(const Elysium::Graphics::PresentMode Value)
{
	_PresentMode = Value;
}

void Elysium::Graphics::PresentationParameters::SetRenderResolution(const Elysium::Core::uint32_t Value)
{
	/*
	if (Value < 50)
	{
		_RenderResolution = 50;
	}
	else if (Value > 200)
	{
		_RenderResolution = 200;
	}
	else
	{
		_RenderResolution = Value;
	}
	*/
	// ToDo: bounds!!
	_RenderResolution = Value;
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

void Elysium::Graphics::PresentationParameters::SetDesiredSurfaceFormat(const Rendering::SurfaceFormat Value)
{
	_DesiredSurfaceFormat = Value;
}

void Elysium::Graphics::PresentationParameters::SetDesiredDepthStencilFormat(const Rendering::DepthFormat Value)
{
	_DesiredDepthStencilFormat = Value;
}
