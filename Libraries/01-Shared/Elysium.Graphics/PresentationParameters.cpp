#include "PresentationParameters.hpp"

Elysium::Graphics::Rendering::PresentationParameters::PresentationParameters(Platform::Canvas& Canvas)
	: _Canvas(Canvas)
{ }
Elysium::Graphics::Rendering::PresentationParameters::~PresentationParameters()
{ }

Elysium::Graphics::Platform::Canvas& Elysium::Graphics::Rendering::PresentationParameters::GetCanvas() const
{
	return _Canvas;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::PresentationParameters::GetBackBufferWidth() const
{
	return _BackBufferWidth;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::PresentationParameters::GetBackBufferHeight() const
{
	return _BackBufferHeight;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::PresentationParameters::GetBackBufferCount() const
{
	return _BackBufferCount;
}

void Elysium::Graphics::Rendering::PresentationParameters::SetBackBufferWidth(const Elysium::Core::uint32_t Value)
{
	_BackBufferWidth = Value;
}

void Elysium::Graphics::Rendering::PresentationParameters::SetBackBufferHeight(const Elysium::Core::uint32_t Value)
{
	_BackBufferHeight = Value;
}

void Elysium::Graphics::Rendering::PresentationParameters::SetBackBufferCount(const Elysium::Core::uint32_t Value)
{
	_BackBufferCount = Value;
}
