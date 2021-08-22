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

Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::FrameBufferVk(const GraphicsDeviceVk& GraphicsDevice, const RenderPassVk& RenderPass, const VkSurfaceKHR NativeSurfaceHandle)
	: _GraphicsDevice(GraphicsDevice), _RenderPass(RenderPass),


	_NativeSurfaceHandle(NativeSurfaceHandle),


	_NativeFramebuffers(_GraphicsDevice._BackBufferImageViews.GetLength())
{
	CreateFramebuffers();

	_GraphicsDevice._Canvas.SizeChanged += Elysium::Core::Delegate<void, const Elysium::Graphics::Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::Bind<Elysium::Graphics::Rendering::Vulkan::FrameBufferVk, &Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::Control_SizeChanged>(*this);
}
Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::~FrameBufferVk()
{
	_GraphicsDevice._Canvas.SizeChanged -= Elysium::Core::Delegate<void, const Elysium::Graphics::Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::Bind<Elysium::Graphics::Rendering::Vulkan::FrameBufferVk, &Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::Control_SizeChanged>(*this);
	
	DestroyFramebuffers();
}

void Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::CreateFramebuffers()
{
	const VkExtent2D& Extent = _GraphicsDevice._NativeSurfaceCapabilities.currentExtent;

	VkResult Result;
	for (size_t i = 0; i < _NativeFramebuffers.GetLength(); i++)
	{
		const VkImageView Attachments[] = { _GraphicsDevice._BackBufferImageViews[i] };

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

		if ((Result = vkCreateFramebuffer(_GraphicsDevice._NativeLogicalDeviceHandle, &FramebufferCreateInfo, nullptr, &_NativeFramebuffers[i])) != VK_SUCCESS)
		{
			throw ExceptionVk(Result);
		}
	}
}

void Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::DestroyFramebuffers()
{
	// wait for any pending queues on the device
	_GraphicsDevice.Wait();

	for (size_t i = 0; i < _NativeFramebuffers.GetLength(); i++)
	{
		vkDestroyFramebuffer(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeFramebuffers[i], nullptr);
	}
}

void Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::Control_SizeChanged(const Elysium::Graphics::Presentation::Control& Sender, const Elysium::Core::int32_t Width, const Elysium::Core::int32_t Height)
{
	DestroyFramebuffers();
	CreateFramebuffers();
}
