#include "GraphicsDeviceVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSPIPELINEVK
#include "GraphicsPipelineVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SHADERMODULEVK
#include "ShaderModuleVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GraphicsDeviceVk(const PhysicalDeviceVk& PhysicalDevice, const GraphicsInstanceVk& GraphicsInstance, PresentationParametersVk& PresentationParameters)
	: _PhysicalDevice(PhysicalDevice), _GraphicsInstance(GraphicsInstance), _PresentationParameters(PresentationParameters),
	_Surface(_GraphicsInstance, _PhysicalDevice, _PresentationParameters), _LogicalDevice(_PhysicalDevice, _Surface, _PresentationParameters),
	_GraphicsQueue(*this, _LogicalDevice.GetGraphicsQueueFamilyIndex(), 0), _PresentationQueue(*this, _LogicalDevice.GetPresentationQueueFamilyIndex(), 0),
	_Swapchain(_LogicalDevice, _Surface, _PresentationParameters), _DefaultRenderPass(_LogicalDevice, _PresentationParameters),
	_FrameBuffer(_LogicalDevice, _Swapchain, _DefaultRenderPass, _PresentationParameters), _DepthBuffer(_LogicalDevice, _Surface, _PresentationParameters),
	_RenderFence(_LogicalDevice, true), _PresentationSemaphore(_LogicalDevice), _RenderSemaphore(_LogicalDevice)
{ }
Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::~GraphicsDeviceVk()
{ }

Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetPresentationParameters() const
{
	return _PresentationParameters;
}

const Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetPhysicalDevice() const
{
	return _PhysicalDevice;
}

const Elysium::Graphics::Rendering::Vulkan::RenderPassVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetDefaultRenderPass() const
{
	return _DefaultRenderPass;
}

const Elysium::Graphics::Rendering::Vulkan::FrameBufferVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetFrameBuffer() const
{
	return _FrameBuffer;
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

Elysium::Graphics::Rendering::Native::INativeGraphicsPipeline* Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateGraphicsPipeline()
{
	return new GraphicsPipelineVk(*this);
}

Elysium::Graphics::Rendering::Native::INativeShaderModule* Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateShaderModule(const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& ByteCode)
{
	return new ShaderModuleVk(*this, ByteCode);
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
