#include "GraphicsDevice.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSDEVICE
#include "INativeGraphicsDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATIONPARAMETERS
#include "PresentationParameters.hpp"
#endif

Elysium::Graphics::Rendering::GraphicsDevice::GraphicsDevice(INativeGraphicsDevice& NativeGraphicsDevice)
	: _NativeGraphicsDevice(NativeGraphicsDevice), _RenderFence((INativeFence&)_NativeGraphicsDevice.GetRenderFence()),
	_PresentationSemaphore((INativeSemaphore&)_NativeGraphicsDevice.GetPresentationSemaphore()),
	_RenderSemaphore((INativeSemaphore&)_NativeGraphicsDevice.GetRenderSemaphore()),
	_GraphicsQueue((INativeQueue&)_NativeGraphicsDevice.GetGraphicsQueue())
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

void Elysium::Graphics::Rendering::GraphicsDevice::Wait() const
{
	_NativeGraphicsDevice.Wait();
}

const bool Elysium::Graphics::Rendering::GraphicsDevice::BeginDraw()
{
	return _NativeGraphicsDevice.BeginDraw();
}

void Elysium::Graphics::Rendering::GraphicsDevice::EndDraw()
{
	_NativeGraphicsDevice.EndDraw();
}
