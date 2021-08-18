#include "GraphicsDeviceVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSPIPELINEVK
#include "GraphicsPipelineVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SHADERMODULEVK
#include "ShaderModuleVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_VERTEXBUFFERVK
#include "VertexBufferVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GraphicsDeviceVk(const PhysicalDeviceVk& PhysicalDevice, const GraphicsInstanceVk& GraphicsInstance, PresentationParametersVk& PresentationParameters)
	: _PhysicalDevice(PhysicalDevice), _GraphicsInstance(GraphicsInstance), _PresentationParameters(PresentationParameters),
	_Surface(_GraphicsInstance, _PhysicalDevice, _PresentationParameters), _LogicalDevice(_PhysicalDevice, _Surface, _PresentationParameters),
	_GraphicsQueue(*this, _LogicalDevice.GetGraphicsQueueFamilyIndex(), 0), _PresentationQueue(*this, _LogicalDevice.GetPresentationQueueFamilyIndex(), 0),
	_Swapchain(_LogicalDevice, _Surface, _PresentationParameters), _DepthBuffer(_LogicalDevice, _Surface, _PresentationParameters),
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

Elysium::Graphics::Rendering::Vulkan::QueueVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetPresentationQueue()
{
	return _PresentationQueue;
}

Elysium::Graphics::Rendering::Native::INativeRenderPass* Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateRenderPass()
{
	return new RenderPassVk(*this);
}

Elysium::Graphics::Rendering::Native::INativeFrameBuffer* Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateFrameBuffer(const Elysium::Graphics::Rendering::Native::INativeRenderPass& RenderPass)
{
	const RenderPassVk& VkRenderPass = reinterpret_cast<const RenderPassVk&>(RenderPass);

	return new FrameBufferVk(*this, VkRenderPass, _Surface);
}

Elysium::Graphics::Rendering::Native::INativeGraphicsPipeline* Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateGraphicsPipeline()
{
	return new GraphicsPipelineVk(*this);
}

Elysium::Graphics::Rendering::Native::INativeVertexBuffer* Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateVertexBuffer(const VertexDeclaration& Declaration, const Elysium::Core::uint32_t VertexCount, const BufferUsage Usage)
{
	return new VertexBufferVk(*this, Declaration, VertexCount, Usage);
}

Elysium::Graphics::Rendering::Native::INativeShaderModule* Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateShaderModule(const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& ByteCode)
{
	return new ShaderModuleVk(*this, ByteCode);
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::Wait() const
{
	_LogicalDevice.Wait();
}

const bool Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::BeginDraw(Native::INativeFence& RenderFence, const Native::INativeSemaphore& PresentationSemaphore)
{
	RenderFence.Wait(Elysium::Core::UInt64::GetMaxValue());
	RenderFence.Reset();
	_Swapchain.AquireNextImage(PresentationSemaphore, Elysium::Core::UInt64::GetMaxValue());

	return true;
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::EndDraw(const Native::INativeSemaphore& RenderSemaphore, const Native::INativeQueue& PresentationQueue)
{
	_Swapchain.PresentFrame(RenderSemaphore, PresentationQueue);
}
