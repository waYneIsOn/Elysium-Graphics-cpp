#include "CommandBufferVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FRAMEBUFFERVK
#include "FramebufferVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSDEVICEVK
#include "GraphicsDeviceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSPIPELINEVK
#include "GraphicsPipelineVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_RENDERPASSVK
#include "RenderPassVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SWAPCHAINVK
#include "SwapchainVk.hpp"
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::CommandBufferVk(const GraphicsDeviceVk& GraphicsDevice, const CommandPoolVk& CommandPool, const bool IsPrimary)
	: _GraphicsDevice(GraphicsDevice), _CommandPool(CommandPool), _IsPrimary(IsPrimary), _NativeCommandBufferHandles(std::move(CreateNativeCommandBuffers()))
{ }
Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::~CommandBufferVk()
{
	DestroyNativeCommandBuffers();
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::Begin()
{
	VkCommandBufferBeginInfo BeginInfo = VkCommandBufferBeginInfo();
	BeginInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	//BeginInfo.flags = VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
	BeginInfo.flags = 0;
	BeginInfo.pNext = nullptr;
	if (_IsPrimary)
	{
		BeginInfo.pInheritanceInfo = nullptr;
	}
	else
	{
		/*
		VkCommandBufferInheritanceInfo InheritanceInfo = VkCommandBufferInheritanceInfo();
		InheritanceInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
		InheritanceInfo.pNext = nullptr;
		//InheritanceInfo.framebuffer
		//InheritanceInfo.occlusionQueryEnable
		//InheritanceInfo.pipelineStatistics
		//InheritanceInfo.renderPass
		//InheritanceInfo.subpass

		BeginInfo.pInheritanceInfo = &InheritanceInfo;
		*/

		throw 1;
	}

	for (size_t i = 0; i < _NativeCommandBufferHandles.GetLength(); i++)
	{
		VkResult Result;
		if ((Result = vkBeginCommandBuffer(_NativeCommandBufferHandles[i], &BeginInfo)) != VK_SUCCESS)
		{
			throw ExceptionVk(Result);
		}
	}
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::End()
{
	for (size_t i = 0; i < _NativeCommandBufferHandles.GetLength(); i++)
	{
		VkResult Result;
		if ((Result = vkEndCommandBuffer(_NativeCommandBufferHandles[i])) != VK_SUCCESS)
		{
			throw ExceptionVk(Result);
		}
	}
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::Reset()
{
	for (size_t i = 0; i < _NativeCommandBufferHandles.GetLength(); i++)
	{
		VkResult Result;
		if ((Result = vkResetCommandBuffer(_NativeCommandBufferHandles[i], VkCommandBufferResetFlagBits::VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT)) != VK_SUCCESS)
		{
			throw ExceptionVk(Result);
		}
	}
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::RecordSecondaryBuffer(const INativeCommandBuffer& CommandBuffer)
{
	/*
	const CommandBufferVk& VkCommandBuffer = static_cast<const CommandBufferVk&>(CommandBuffer);
	for (size_t i = 0; i < _NativeCommandBufferHandles.GetLength(); i++)
	{
		vkCmdExecuteCommands(_NativeCommandBufferHandles[i], VkCommandBuffer._NativeCommandBufferHandles.GetLength(),
			&VkCommandBuffer._NativeCommandBufferHandles[0]);
	}
	*/
	throw 1;
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::BeginRenderPass(const Native::INativeRenderPass& RenderPass, const Native::INativeFrameBuffer& FrameBuffer)
{
	const PresentationParametersVk& PresentationParameter = _GraphicsDevice.GetPresentationParameters();
	const VkExtent2D& Extent = (const VkExtent2D&)PresentationParameter.GetExtent();
	const RenderPassVk& VkRenderPass = static_cast<const RenderPassVk&>(RenderPass);
	const FrameBufferVk& VkFrameBuffer = static_cast<const FrameBufferVk&>(FrameBuffer);

	VkClearValue ClearValues[1];
	ClearValues[0].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	ClearValues[0].depthStencil.depth = 0.0f;
	ClearValues[0].depthStencil.stencil = 0;

	for (size_t i = 0; i < _NativeCommandBufferHandles.GetLength(); i++)
	{
		VkRenderPassBeginInfo RenderPassInfo = VkRenderPassBeginInfo();
		RenderPassInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		RenderPassInfo.framebuffer = VkFrameBuffer._NativeSwapchainFramebufferHandles[i];
		RenderPassInfo.renderArea.offset = { 0, 0 };
		RenderPassInfo.renderArea.extent = Extent;
		RenderPassInfo.renderPass = VkRenderPass._NativeRenderPassHandle;
		RenderPassInfo.clearValueCount = 1;
		RenderPassInfo.pClearValues = &ClearValues[0];

		vkCmdBeginRenderPass(_NativeCommandBufferHandles[i], &RenderPassInfo, VkSubpassContents::VK_SUBPASS_CONTENTS_INLINE);
	}
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::EndRenderPass()
{
	for (size_t i = 0; i < _NativeCommandBufferHandles.GetLength(); i++)
	{
		vkCmdEndRenderPass(_NativeCommandBufferHandles[i]);
	}
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::SetGraphicsPipeline(const Native::INativeGraphicsPipeline& GraphicsPipeline)
{
	const GraphicsPipelineVk& VkPipeline = static_cast<const GraphicsPipelineVk&>(GraphicsPipeline);
	
	for (size_t i = 0; i < _NativeCommandBufferHandles.GetLength(); i++)
	{
		vkCmdBindPipeline(_NativeCommandBufferHandles[i], VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipeline._NativePipelineHandle);
	}
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::Draw(Elysium::Core::uint32_t VertexCount, Elysium::Core::uint32_t InstanceCount, Elysium::Core::uint32_t FirstVertex, Elysium::Core::uint32_t FirstInstance)
{
	for (size_t i = 0; i < _NativeCommandBufferHandles.GetLength(); i++)
	{
		vkCmdDraw(_NativeCommandBufferHandles[i], VertexCount, InstanceCount, FirstVertex, FirstInstance);
	}
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::ClearBackBufferImage(const Color& ClearColor)
{
	VkImageSubresourceRange ImageSubresourceRange = VkImageSubresourceRange();
	ImageSubresourceRange.baseArrayLayer = 0;
	ImageSubresourceRange.baseMipLevel = 0;
	ImageSubresourceRange.layerCount = 1;
	ImageSubresourceRange.levelCount = 1;
	ImageSubresourceRange.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;

	const PresentationParametersVk& PresentationParameters = static_cast<const PresentationParametersVk&>(_GraphicsDevice.GetPresentationParameters());
	const SwapchainVk& Swapchain = _GraphicsDevice._Swapchain;
	for (size_t i = 0; i < _NativeCommandBufferHandles.GetLength(); i++)
	{
		VkImage BackbufferImage = Swapchain._BackBufferImages[i];
		
		// ... "write transfer"
		VkImageMemoryBarrier PresentToClearBarrier = VkImageMemoryBarrier();
		PresentToClearBarrier.sType = VkStructureType::VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		PresentToClearBarrier.pNext = nullptr;
		PresentToClearBarrier.image = BackbufferImage;
		PresentToClearBarrier.subresourceRange = ImageSubresourceRange;
		PresentToClearBarrier.srcQueueFamilyIndex = _GraphicsDevice._LogicalDevice.GetPresentationQueueFamilyIndex();
		PresentToClearBarrier.dstQueueFamilyIndex = _GraphicsDevice._LogicalDevice.GetPresentationQueueFamilyIndex();
		PresentToClearBarrier.srcAccessMask = VkAccessFlagBits::VK_ACCESS_MEMORY_READ_BIT;
		PresentToClearBarrier.dstAccessMask = VkAccessFlagBits::VK_ACCESS_TRANSFER_WRITE_BIT;
		PresentToClearBarrier.oldLayout = VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;
		PresentToClearBarrier.newLayout = VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;

		vkCmdPipelineBarrier(_NativeCommandBufferHandles[i], VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0,
			nullptr, 0, nullptr, 1, &PresentToClearBarrier);
		
		// ... actual command
		float Red = ClearColor.GetRed() / 255.0f;
		float Green = ClearColor.GetGreen() / 255.0f;
		float Blue = ClearColor.GetBlue() / 255.0f;
		float Alpha = ClearColor.GetAlpha() / 255.0f;
		VkClearColorValue ClearColorValue = { Red, Green, Blue, Alpha };

		vkCmdClearColorImage(_NativeCommandBufferHandles[i], BackbufferImage, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			&ClearColorValue, 1, &ImageSubresourceRange);
		
		// ... "read memory"
		VkImageMemoryBarrier ClearToPresentBarrier = VkImageMemoryBarrier();
		ClearToPresentBarrier.sType = VkStructureType::VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		ClearToPresentBarrier.pNext = nullptr;
		ClearToPresentBarrier.image = BackbufferImage;
		ClearToPresentBarrier.subresourceRange = ImageSubresourceRange;
		ClearToPresentBarrier.srcQueueFamilyIndex = _GraphicsDevice._LogicalDevice.GetPresentationQueueFamilyIndex();
		ClearToPresentBarrier.dstQueueFamilyIndex = _GraphicsDevice._LogicalDevice.GetPresentationQueueFamilyIndex();
		ClearToPresentBarrier.srcAccessMask = VkAccessFlagBits::VK_ACCESS_TRANSFER_WRITE_BIT;
		ClearToPresentBarrier.dstAccessMask = VkAccessFlagBits::VK_ACCESS_MEMORY_READ_BIT;
		ClearToPresentBarrier.oldLayout = VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		ClearToPresentBarrier.newLayout = VkImageLayout::VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		vkCmdPipelineBarrier(_NativeCommandBufferHandles[i], VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			VkPipelineStageFlagBits::VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0,
			nullptr, 0, nullptr, 1, &ClearToPresentBarrier);
	}
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::ClearDepthImage(const float Depth, const Elysium::Core::int32_t Stencil)
{
	VkImageSubresourceRange ImageSubresourceRange = VkImageSubresourceRange();
	ImageSubresourceRange.baseArrayLayer = 0;
	ImageSubresourceRange.baseMipLevel = 0;
	ImageSubresourceRange.layerCount = 1;
	ImageSubresourceRange.levelCount = 1;
	ImageSubresourceRange.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_DEPTH_BIT | VkImageAspectFlagBits::VK_IMAGE_ASPECT_STENCIL_BIT;

	const PresentationParametersVk& PresentationParameters = static_cast<const PresentationParametersVk&>(_GraphicsDevice.GetPresentationParameters());
	const DepthBufferVk& DepthBuffer = _GraphicsDevice._DepthBuffer;
	VkImage DepthBufferImage = DepthBuffer._NativeDepthImageHandle;

	for (size_t i = 0; i < _NativeCommandBufferHandles.GetLength(); i++)
	{
		// ... "write transfer"
		VkImageMemoryBarrier PresentToClearBarrier = VkImageMemoryBarrier();
		PresentToClearBarrier.sType = VkStructureType::VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		PresentToClearBarrier.pNext = nullptr;
		PresentToClearBarrier.image = DepthBufferImage;
		PresentToClearBarrier.subresourceRange = ImageSubresourceRange;
		PresentToClearBarrier.srcQueueFamilyIndex = _GraphicsDevice._LogicalDevice.GetPresentationQueueFamilyIndex();
		PresentToClearBarrier.dstQueueFamilyIndex = _GraphicsDevice._LogicalDevice.GetPresentationQueueFamilyIndex();
		PresentToClearBarrier.srcAccessMask = VkAccessFlagBits::VK_ACCESS_MEMORY_READ_BIT;
		PresentToClearBarrier.dstAccessMask = VkAccessFlagBits::VK_ACCESS_TRANSFER_WRITE_BIT;
		PresentToClearBarrier.oldLayout = VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;
		PresentToClearBarrier.newLayout = VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;

		vkCmdPipelineBarrier(_NativeCommandBufferHandles[i], VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0,
			nullptr, 0, nullptr, 1, &PresentToClearBarrier);

		// ... actual command
		VkClearDepthStencilValue ClearDepthStencilValue = VkClearDepthStencilValue();
		ClearDepthStencilValue.depth = Depth;
		ClearDepthStencilValue.stencil = Stencil;

		vkCmdClearDepthStencilImage(_NativeCommandBufferHandles[i], DepthBufferImage, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			&ClearDepthStencilValue, 1, &ImageSubresourceRange);

		// ... "read memory"
		VkImageMemoryBarrier ClearToPresentBarrier = VkImageMemoryBarrier();
		ClearToPresentBarrier.sType = VkStructureType::VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		ClearToPresentBarrier.pNext = nullptr;
		ClearToPresentBarrier.image = DepthBufferImage;
		ClearToPresentBarrier.subresourceRange = ImageSubresourceRange;
		ClearToPresentBarrier.srcQueueFamilyIndex = _GraphicsDevice._LogicalDevice.GetPresentationQueueFamilyIndex();
		ClearToPresentBarrier.dstQueueFamilyIndex = _GraphicsDevice._LogicalDevice.GetPresentationQueueFamilyIndex();
		ClearToPresentBarrier.srcAccessMask = VkAccessFlagBits::VK_ACCESS_TRANSFER_WRITE_BIT;
		ClearToPresentBarrier.dstAccessMask = VkAccessFlagBits::VK_ACCESS_MEMORY_READ_BIT;
		ClearToPresentBarrier.oldLayout = VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		ClearToPresentBarrier.newLayout = VkImageLayout::VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		vkCmdPipelineBarrier(_NativeCommandBufferHandles[i], VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			VkPipelineStageFlagBits::VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0,
			nullptr, 0, nullptr, 1, &ClearToPresentBarrier);
	}

}

Elysium::Core::Collections::Template::Array<VkCommandBuffer> Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::CreateNativeCommandBuffers()
{
	PresentationParameters& PresentationParameters = _GraphicsDevice.GetPresentationParameters();

	VkCommandBufferAllocateInfo  AllocateInfo = VkCommandBufferAllocateInfo();
	AllocateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	AllocateInfo.pNext = nullptr;
	AllocateInfo.commandPool = _CommandPool._NativeCommandPoolHandle;
	AllocateInfo.level = _IsPrimary == true ? VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY : VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_SECONDARY;
	AllocateInfo.commandBufferCount = PresentationParameters.GetBackBufferCount();

	VkResult Result;
	Elysium::Core::Collections::Template::Array<VkCommandBuffer> NativeCommandBufferHandles = 
		Elysium::Core::Collections::Template::Array<VkCommandBuffer>(AllocateInfo.commandBufferCount);
	if ((Result = vkAllocateCommandBuffers(_CommandPool._GraphicsDevice._LogicalDevice._NativeLogicalDeviceHandle, &AllocateInfo, &NativeCommandBufferHandles[0])) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	return NativeCommandBufferHandles;
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::DestroyNativeCommandBuffers()
{
	const PresentationParameters& PresentationParameters = _GraphicsDevice.GetPresentationParameters();
	vkFreeCommandBuffers(_GraphicsDevice._LogicalDevice._NativeLogicalDeviceHandle, _CommandPool._NativeCommandPoolHandle, _NativeCommandBufferHandles.GetLength(), &_NativeCommandBufferHandles[0]);
}
