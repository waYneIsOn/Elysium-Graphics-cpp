#include "GraphicsDevice.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSDEVICE
#include "INativeGraphicsDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATIONPARAMETERS
#include "PresentationParameters.hpp"
#endif

Elysium::Graphics::Rendering::GraphicsDevice::GraphicsDevice(Native::INativeGraphicsDevice& NativeGraphicsDevice)
	: _NativeGraphicsDevice(NativeGraphicsDevice),
	_RenderFence((Native::INativeFence&)_NativeGraphicsDevice.GetRenderFence()),
	_PresentationSemaphore((Native::INativeSemaphore&)_NativeGraphicsDevice.GetPresentationSemaphore()),
	_RenderSemaphore((Native::INativeSemaphore&)_NativeGraphicsDevice.GetRenderSemaphore()),
	_GraphicsQueue((Native::INativeQueue&)_NativeGraphicsDevice.GetGraphicsQueue()),
	_PresentationQueue((Native::INativeQueue&)_NativeGraphicsDevice.GetPresentationQueue())
{ }
Elysium::Graphics::Rendering::GraphicsDevice::~GraphicsDevice()
{ }

Elysium::Graphics::PresentationParameters& Elysium::Graphics::Rendering::GraphicsDevice::GetPresentationParameters()
{
	return _NativeGraphicsDevice.GetPresentationParameters();
}

const Elysium::Graphics::Rendering::Fence& Elysium::Graphics::Rendering::GraphicsDevice::GetRenderFence() const
{
	return _RenderFence;
}

const Elysium::Graphics::Rendering::Semaphore& Elysium::Graphics::Rendering::GraphicsDevice::GetPresentationSemaphore() const
{
	return _PresentationSemaphore;
}

const Elysium::Graphics::Rendering::Semaphore& Elysium::Graphics::Rendering::GraphicsDevice::GetRenderSemaphore() const
{
	return _RenderSemaphore;
}

Elysium::Graphics::Rendering::Queue& Elysium::Graphics::Rendering::GraphicsDevice::GetGraphicsQueue()
{
	return _GraphicsQueue;
}

Elysium::Graphics::Rendering::Queue& Elysium::Graphics::Rendering::GraphicsDevice::GetPresentationQueue()
{
	return _PresentationQueue;
}

void Elysium::Graphics::Rendering::GraphicsDevice::Wait() const
{
	_NativeGraphicsDevice.Wait();
}

const bool Elysium::Graphics::Rendering::GraphicsDevice::BeginDraw()
{
	return _NativeGraphicsDevice.BeginDraw(_RenderFence._NativeFence, _PresentationSemaphore._NativeSemaphore);
}

void Elysium::Graphics::Rendering::GraphicsDevice::EndDraw()
{
	_NativeGraphicsDevice.EndDraw(_RenderSemaphore._NativeSemaphore, _PresentationQueue._NativeQueue);
}
