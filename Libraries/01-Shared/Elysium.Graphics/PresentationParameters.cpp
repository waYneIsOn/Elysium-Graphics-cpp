#include "PresentationParameters.hpp"

Elysium::Graphics::Rendering::PresentationParameters::PresentationParameters(const Platform::Canvas& Canvas)
	: _Canvas(Canvas)
{ }
Elysium::Graphics::Rendering::PresentationParameters::~PresentationParameters()
{ }

const Elysium::Graphics::Platform::Canvas& Elysium::Graphics::Rendering::PresentationParameters::GetCanvas() const
{
	return _Canvas;
}
