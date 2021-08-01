#include "Semaphore.hpp"

Elysium::Graphics::Rendering::Semaphore::~Semaphore()
{ }

void Elysium::Graphics::Rendering::Semaphore::Wait(const Elysium::Core::uint64_t Timeout)
{
	_NativeSemaphore.Wait(Timeout);
}

Elysium::Graphics::Rendering::Semaphore::Semaphore(INativeSemaphore& NativeSemaphore)
	: _NativeSemaphore(NativeSemaphore)
{ }
