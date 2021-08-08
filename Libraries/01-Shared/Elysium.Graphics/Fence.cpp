#include "Fence.hpp"

Elysium::Graphics::Rendering::Fence::~Fence()
{ }

void Elysium::Graphics::Rendering::Fence::Wait(const Elysium::Core::uint64_t Timeout) const
{
	_NativeFence.Wait(Timeout);
}

void Elysium::Graphics::Rendering::Fence::Reset()
{
	_NativeFence.Reset();
}

Elysium::Graphics::Rendering::Fence::Fence(Native::INativeFence& NativeFence)
	: _NativeFence(NativeFence)
{ }
