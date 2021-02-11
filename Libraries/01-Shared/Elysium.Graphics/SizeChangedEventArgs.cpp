#include "SizeChangedEventArgs.hpp"

Elysium::Graphics::Platform::SizeChangedEventArgs::SizeChangedEventArgs(const Elysium::Core::uint32_t Width, const Elysium::Core::uint32_t Height)
	: _Width(Width), _Height(Height)
{ }
Elysium::Graphics::Platform::SizeChangedEventArgs::~SizeChangedEventArgs()
{ }

const Elysium::Core::uint32_t& Elysium::Graphics::Platform::SizeChangedEventArgs::GetWidth() const
{
	return _Width;
}

const Elysium::Core::uint32_t& Elysium::Graphics::Platform::SizeChangedEventArgs::GetHeight() const
{
	return _Height;
}
