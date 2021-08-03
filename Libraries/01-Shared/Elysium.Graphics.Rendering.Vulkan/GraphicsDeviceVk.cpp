#include "GraphicsDeviceVk.hpp"

Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GraphicsDeviceVk(GraphicsInstanceVk& GraphicsInstance, PresentationParametersVk& PresentationParameters)
	: _GraphicsInstance(GraphicsInstance), _PresentationParameters(PresentationParameters),
	_Surface(_GraphicsInstance, PresentationParameters), 
	_LogicalDevice(static_cast<const PhysicalDeviceVk&>(PresentationParameters.GetGraphicsDevice()), PresentationParameters),
	_GraphicsQueue(*this, _LogicalDevice, PresentationParameters.GetGraphicsQueueFamilyIndex(), 0),
	_PresentationQueue(*this, _LogicalDevice, PresentationParameters.GetPresentationQueueFamilyIndex(), 0),
	_Swapchain(_Surface, _LogicalDevice), _DefaultRenderPass(_LogicalDevice), _FrameBuffer(_LogicalDevice, _Swapchain, _DefaultRenderPass),
	_DepthBuffer(_Surface, _LogicalDevice), _RenderFence(_LogicalDevice, true), _PresentationSemaphore(_LogicalDevice), _RenderSemaphore(_LogicalDevice)
{ }
Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::~GraphicsDeviceVk()
{ }

const Elysium::Graphics::Rendering::Vulkan::GraphicsInstanceVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetGraphicsAPI() const
{
	return _GraphicsInstance;
}

Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetPresentationParameters()
{
	return _PresentationParameters;
}

const Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetPhysicalDevice() const
{
	return (Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk&)_PresentationParameters.GetGraphicsDevice();
}

const Elysium::Graphics::Rendering::Vulkan::FenceVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetRenderFence() const
{
	return _RenderFence;
}

const Elysium::Graphics::Rendering::Vulkan::SemaphoreVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetPresentationSemaphore() const
{
	return _PresentationSemaphore;
}

const Elysium::Graphics::Rendering::Vulkan::SemaphoreVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetRenderSemaphore() const
{
	return _RenderSemaphore;
}

Elysium::Graphics::Rendering::Vulkan::QueueVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetGraphicsQueue()
{
	return _GraphicsQueue;
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::Wait() const
{
	_LogicalDevice.Wait();
}

const bool Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::BeginDraw()
{
	_RenderFence.Wait(Elysium::Core::UInt64::GetMaxValue());
	_RenderFence.Reset();
	_Swapchain.AquireNextImage(_PresentationSemaphore, Elysium::Core::UInt64::GetMaxValue());

	return true;
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::EndDraw()
{
	_Swapchain.PresentFrame(_RenderSemaphore, _PresentationQueue);
}
