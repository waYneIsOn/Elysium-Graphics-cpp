#include "FrameBufferVk.hpp"

#ifndef ELYSIUM_CORE_DELEGATE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Delegate.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSDEVICEVK
#include "GraphicsDeviceVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::FrameBufferVk(const GraphicsDeviceVk& GraphicsDevice, const RenderPassVk& RenderPass, SurfaceVk& Surface)
	: _GraphicsDevice(GraphicsDevice), _RenderPass(RenderPass), _Surface(Surface),
	_NativeSwapchainFramebufferHandles(_GraphicsDevice._Swapchain._BackBufferImageViews.GetLength())
{
	CreateFramebuffers();
	_Surface.SizeChanged += Elysium::Core::Delegate<void, const Elysium::Graphics::Rendering::Vulkan::SurfaceVk&>::Bind<Elysium::Graphics::Rendering::Vulkan::FrameBufferVk, &Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::Surface_OnSizeChanged>(*this);
}
Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::~FrameBufferVk()
{
	_Surface.SizeChanged -= Elysium::Core::Delegate<void, const Elysium::Graphics::Rendering::Vulkan::SurfaceVk&>::Bind<Elysium::Graphics::Rendering::Vulkan::FrameBufferVk, &Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::Surface_OnSizeChanged>(*this);
	DestroyFramebuffers();
}

void Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::CreateFramebuffers()
{
	const VkExtent2D& Extent = (const VkExtent2D&)_GraphicsDevice._PresentationParameters.GetExtent();

	VkResult Result;
	for (size_t i = 0; i < _NativeSwapchainFramebufferHandles.GetLength(); i++)
	{
		const VkImageView Attachments[] = { _GraphicsDevice._Swapchain._BackBufferImageViews[i] };

		VkFramebufferCreateInfo FramebufferCreateInfo = VkFramebufferCreateInfo();
		FramebufferCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		FramebufferCreateInfo.pNext = nullptr;
		FramebufferCreateInfo.flags = 0;
		FramebufferCreateInfo.renderPass = _RenderPass._NativeRenderPassHandle;
		FramebufferCreateInfo.attachmentCount = 1;
		FramebufferCreateInfo.pAttachments = &Attachments[0];
		FramebufferCreateInfo.width = Extent.width;
		FramebufferCreateInfo.height = Extent.height;
		FramebufferCreateInfo.layers = 1;

		if ((Result = vkCreateFramebuffer(_GraphicsDevice._LogicalDevice._NativeLogicalDeviceHandle, &FramebufferCreateInfo, nullptr, &_NativeSwapchainFramebufferHandles[i])) != VK_SUCCESS)
		{
			throw ExceptionVk(Result);
		}
	}
}

void Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::DestroyFramebuffers()
{
	// wait for any pending queues on the device
	_GraphicsDevice._LogicalDevice.Wait();

	for (size_t i = 0; i < _NativeSwapchainFramebufferHandles.GetLength(); i++)
	{
		vkDestroyFramebuffer(_GraphicsDevice._LogicalDevice._NativeLogicalDeviceHandle, _NativeSwapchainFramebufferHandles[i], nullptr);
	}
}

void Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::Surface_OnSizeChanged(const Elysium::Graphics::Rendering::Vulkan::SurfaceVk& Sender)
{
	DestroyFramebuffers();
	CreateFramebuffers();
}
