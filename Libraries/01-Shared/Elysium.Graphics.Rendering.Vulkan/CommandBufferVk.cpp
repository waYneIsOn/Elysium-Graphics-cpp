#include "CommandBufferVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_COMMANDPOOLVK
#include "CommandPoolVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FORMATCONVERTERVK
#include "FormatConverterVk.hpp"
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

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_VERTEXBUFFERVK
#include "VertexBufferVk.hpp"
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

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::BeginRecording()
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

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::EndRecording()
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

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::RecordBeginRenderPass(const Native::INativeRenderPass& RenderPass,
	const Native::INativeFrameBuffer& FrameBuffer, const Color& ClearColor, const float Depth, const Elysium::Core::uint32_t Stencil)
{
	const PresentationParametersVk& PresentationParameter = _GraphicsDevice.GetPresentationParameters();
	const VkExtent2D& Extent = _GraphicsDevice._NativeSurfaceCapabilities.currentExtent;
	const RenderPassVk& VkRenderPass = static_cast<const RenderPassVk&>(RenderPass);
	const FrameBufferVk& VkFrameBuffer = static_cast<const FrameBufferVk&>(FrameBuffer);

	VkClearValue ClearValues = VkClearValue();
	ClearValues.depthStencil.depth = Depth;
	ClearValues.depthStencil.stencil = Stencil;
	ClearValues.color = { ClearColor.GetRed() / 255.0f, ClearColor.GetGreen() / 255.0f, ClearColor.GetBlue() / 255.0f, ClearColor.GetAlpha() / 255.0f };

	for (size_t i = 0; i < _NativeCommandBufferHandles.GetLength(); i++)
	{
		VkRenderPassBeginInfo RenderPassInfo = VkRenderPassBeginInfo();
		RenderPassInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		RenderPassInfo.framebuffer = VkFrameBuffer._NativeFramebuffers[i];
		RenderPassInfo.renderArea.offset = { 0, 0 };
		RenderPassInfo.renderArea.extent.width = VkFrameBuffer._Extent.width;
		RenderPassInfo.renderArea.extent.height = VkFrameBuffer._Extent.height;
		RenderPassInfo.renderPass = VkRenderPass._NativeRenderPassHandle;
		RenderPassInfo.clearValueCount = 1;
		RenderPassInfo.pClearValues = &ClearValues;
		
		VkSubpassContents SubpassContents = _IsPrimary ? VkSubpassContents::VK_SUBPASS_CONTENTS_INLINE : VkSubpassContents::VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS;

		vkCmdBeginRenderPass(_NativeCommandBufferHandles[i], &RenderPassInfo, SubpassContents);
	}
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::RecordEndRenderPass()
{
	for (size_t i = 0; i < _NativeCommandBufferHandles.GetLength(); i++)
	{
		vkCmdEndRenderPass(_NativeCommandBufferHandles[i]);
	}
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::RecordSetGraphicsPipeline(const Native::INativeGraphicsPipeline& GraphicsPipeline)
{
	const GraphicsPipelineVk& VkPipeline = static_cast<const GraphicsPipelineVk&>(GraphicsPipeline);
	
	for (size_t i = 0; i < _NativeCommandBufferHandles.GetLength(); i++)
	{
		vkCmdBindPipeline(_NativeCommandBufferHandles[i], VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipeline._NativePipelineHandle);
	}
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::RecordSetVertexBuffer(const Native::INativeVertexBuffer& VertexBuffer)
{
	const VertexBufferVk& VkVertexBuffer = static_cast<const VertexBufferVk&>(VertexBuffer);

	VkBuffer VertexBuffers[] = { VkVertexBuffer._NativeVertexBuffer };
	VkDeviceSize Offsets[] = { 0 };
	for (size_t i = 0; i < _NativeCommandBufferHandles.GetLength(); i++)
	{
		vkCmdBindVertexBuffers(_NativeCommandBufferHandles[i], 0, 1, VertexBuffers, Offsets);
	}
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::RecordDraw(Elysium::Core::uint32_t VertexCount, Elysium::Core::uint32_t InstanceCount, Elysium::Core::uint32_t FirstVertex, Elysium::Core::uint32_t FirstInstance)
{
	for (size_t i = 0; i < _NativeCommandBufferHandles.GetLength(); i++)
	{
		vkCmdDraw(_NativeCommandBufferHandles[i], VertexCount, InstanceCount, FirstVertex, FirstInstance);
	}
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::RecordBlit(const Native::INativeFrameBuffer& FrameBuffer, const BlitFilter Filter)
{
	const FrameBufferVk& VkFrameBuffer = static_cast<const FrameBufferVk&>(FrameBuffer);
	const VkExtent2D& BackBufferExtent = _GraphicsDevice._NativeSurfaceCapabilities.currentExtent;
	const size_t Length = _NativeCommandBufferHandles.GetLength();

	VkImageSubresourceRange ImageSubresourceRange = VkImageSubresourceRange();
	ImageSubresourceRange.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
	ImageSubresourceRange.baseArrayLayer = 0;
	ImageSubresourceRange.baseMipLevel = 0;
	ImageSubresourceRange.layerCount = 1;
	ImageSubresourceRange.levelCount = 1;

	VkImageLayout SourceImageLayout = VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
	VkImageLayout TargetImageLayout = VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;

	VkImageBlit ImageBlit = VkImageBlit();
	ImageBlit.srcOffsets[0].x = 0;
	ImageBlit.srcOffsets[0].y = 0;
	ImageBlit.srcOffsets[0].z = 0;
	ImageBlit.srcOffsets[1].x = VkFrameBuffer._Extent.width;
	ImageBlit.srcOffsets[1].y = VkFrameBuffer._Extent.height;
	ImageBlit.srcOffsets[1].z = VkFrameBuffer._Extent.depth;
	ImageBlit.srcSubresource.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
	ImageBlit.srcSubresource.baseArrayLayer = 0;
	ImageBlit.srcSubresource.layerCount = 1;
	ImageBlit.srcSubresource.mipLevel = 0;

	ImageBlit.dstOffsets[0].x = 0;
	ImageBlit.dstOffsets[0].y = 0;
	ImageBlit.dstOffsets[0].z = 0;
	ImageBlit.dstOffsets[1].x = BackBufferExtent.width;
	ImageBlit.dstOffsets[1].y = BackBufferExtent.height;
	ImageBlit.dstOffsets[1].z = 1;
	ImageBlit.dstSubresource.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
	ImageBlit.dstSubresource.baseArrayLayer = 0;
	ImageBlit.dstSubresource.layerCount = 1;
	ImageBlit.dstSubresource.mipLevel = 0;

	for (size_t i = 0; i < Length; i++)
	{
		VkCommandBuffer CurrentCommandBuffer = _NativeCommandBufferHandles[i];
		VkImage CurrentBackBufferImage = _GraphicsDevice._BackBufferImages[i];
		VkImage CurrentFrameBufferImage = VkFrameBuffer._NativeImages[i];

		// Transition source image (framebuffer) to "read transfer"
		RecordInsertImageMemoryBarrier(CurrentCommandBuffer, CurrentFrameBufferImage,
			VkAccessFlagBits::VK_ACCESS_MEMORY_READ_BIT, VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			VkAccessFlagBits::VK_ACCESS_TRANSFER_READ_BIT, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			ImageSubresourceRange);

		// Transition target image (backbuffer) to "write transfer"
		RecordInsertImageMemoryBarrier(CurrentCommandBuffer, CurrentBackBufferImage,
			0, VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			VkAccessFlagBits::VK_ACCESS_TRANSFER_WRITE_BIT, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			ImageSubresourceRange);

		// Record actual command
		vkCmdBlitImage(CurrentCommandBuffer, CurrentFrameBufferImage, SourceImageLayout, CurrentBackBufferImage, TargetImageLayout, 1, &ImageBlit, 
			FormatConverterVk::Convert(Filter));

		// Transition target image (backbuffer) to "read memory"
		RecordInsertImageMemoryBarrier(CurrentCommandBuffer, CurrentBackBufferImage,
			VkAccessFlagBits::VK_ACCESS_TRANSFER_WRITE_BIT, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			VkAccessFlagBits::VK_ACCESS_MEMORY_READ_BIT, VkImageLayout::VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			ImageSubresourceRange);

		// Transition source image (framebuffer) to "read memory"
		RecordInsertImageMemoryBarrier(CurrentCommandBuffer, CurrentFrameBufferImage,
			VkAccessFlagBits::VK_ACCESS_TRANSFER_READ_BIT, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			VkAccessFlagBits::VK_ACCESS_MEMORY_READ_BIT, VkImageLayout::VK_IMAGE_LAYOUT_GENERAL, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			ImageSubresourceRange);
	}
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::RecordClearBackBufferColorImage(const Color& ClearColor)
{
	VkImageSubresourceRange ImageSubresourceRange = VkImageSubresourceRange();
	ImageSubresourceRange.baseArrayLayer = 0;
	ImageSubresourceRange.baseMipLevel = 0;
	ImageSubresourceRange.layerCount = 1;
	ImageSubresourceRange.levelCount = 1;
	ImageSubresourceRange.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;

	VkClearColorValue ClearColorValue = { ClearColor.GetRed() / 255.0f, ClearColor.GetGreen() / 255.0f, ClearColor.GetBlue() / 255.0f, ClearColor.GetAlpha() / 255.0f };

	for (size_t i = 0; i < _NativeCommandBufferHandles.GetLength(); i++)
	{
		VkCommandBuffer CurrentCommandBuffer = _NativeCommandBufferHandles[i];
		VkImage CurrentBackBufferImage = _GraphicsDevice._BackBufferImages[i];

		// Transition backbuffer-image to "write transfer"
		RecordInsertImageMemoryBarrier(CurrentCommandBuffer, CurrentBackBufferImage,
			VkAccessFlagBits::VK_ACCESS_MEMORY_READ_BIT, VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			VkAccessFlagBits::VK_ACCESS_TRANSFER_WRITE_BIT, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			ImageSubresourceRange);

		// Record actual command
		vkCmdClearColorImage(_NativeCommandBufferHandles[i], CurrentBackBufferImage, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			&ClearColorValue, 1, &ImageSubresourceRange);

		// Transition backbuffer-image to "read memory"
		RecordInsertImageMemoryBarrier(CurrentCommandBuffer, CurrentBackBufferImage,
			VkAccessFlagBits::VK_ACCESS_TRANSFER_WRITE_BIT, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			VkAccessFlagBits::VK_ACCESS_MEMORY_READ_BIT, VkImageLayout::VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
			ImageSubresourceRange);
	}
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::RecordClearBackBufferDepthImage(const float Depth, const Elysium::Core::uint32_t Stencil)
{
	VkImageSubresourceRange ImageSubresourceRange = VkImageSubresourceRange();
	ImageSubresourceRange.baseArrayLayer = 0;
	ImageSubresourceRange.baseMipLevel = 0;
	ImageSubresourceRange.layerCount = 1;
	ImageSubresourceRange.levelCount = 1;
	ImageSubresourceRange.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_DEPTH_BIT | VkImageAspectFlagBits::VK_IMAGE_ASPECT_STENCIL_BIT;

	const PresentationParametersVk& PresentationParameters = static_cast<const PresentationParametersVk&>(_GraphicsDevice.GetPresentationParameters());
	const VkImage& DepthBufferImage = _GraphicsDevice._NativeDepthImageHandle;

	for (size_t i = 0; i < _NativeCommandBufferHandles.GetLength(); i++)
	{
		VkCommandBuffer CurrentCommandBuffer = _NativeCommandBufferHandles[i];

		// Transition backbuffer-image to "write transfer"
		RecordInsertImageMemoryBarrier(CurrentCommandBuffer, DepthBufferImage,
			VkAccessFlagBits::VK_ACCESS_MEMORY_READ_BIT, VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			VkAccessFlagBits::VK_ACCESS_TRANSFER_WRITE_BIT, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			ImageSubresourceRange);
		
		// Record actual command
		VkClearDepthStencilValue ClearDepthStencilValue = VkClearDepthStencilValue();
		ClearDepthStencilValue.depth = Depth;
		ClearDepthStencilValue.stencil = Stencil;

		vkCmdClearDepthStencilImage(_NativeCommandBufferHandles[i], DepthBufferImage, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			&ClearDepthStencilValue, 1, &ImageSubresourceRange);

		// Transition backbuffer-image to "read memory"
		RecordInsertImageMemoryBarrier(CurrentCommandBuffer, DepthBufferImage,
			VkAccessFlagBits::VK_ACCESS_TRANSFER_WRITE_BIT, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			VkAccessFlagBits::VK_ACCESS_MEMORY_READ_BIT, VkImageLayout::VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VkPipelineStageFlagBits::VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
			ImageSubresourceRange);
	}

}

Elysium::Core::Collections::Template::Array<VkCommandBuffer> Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::CreateNativeCommandBuffers()
{
	const PresentationParameters& PresentationParameters = _GraphicsDevice.GetPresentationParameters();

	VkCommandBufferAllocateInfo  AllocateInfo = VkCommandBufferAllocateInfo();
	AllocateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	AllocateInfo.pNext = nullptr;
	AllocateInfo.commandPool = _CommandPool._NativeCommandPoolHandle;
	AllocateInfo.level = _IsPrimary == true ? VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY : VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_SECONDARY;
	AllocateInfo.commandBufferCount = PresentationParameters.GetBackBufferCount();

	VkResult Result;
	Elysium::Core::Collections::Template::Array<VkCommandBuffer> NativeCommandBufferHandles = 
		Elysium::Core::Collections::Template::Array<VkCommandBuffer>(AllocateInfo.commandBufferCount);
	if ((Result = vkAllocateCommandBuffers(_CommandPool._GraphicsDevice._NativeLogicalDeviceHandle, &AllocateInfo, &NativeCommandBufferHandles[0])) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	return NativeCommandBufferHandles;
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::RecordInsertImageMemoryBarrier(const VkCommandBuffer CommandBuffer, const VkImage Image,
	const VkAccessFlags SourceAccessMask, const VkImageLayout OldLayout, const VkPipelineStageFlags SourceStageFlags,
	const VkAccessFlags TargetAccessMask, const VkImageLayout NewLayout, const VkPipelineStageFlags TargetStageFlags,
	const VkImageSubresourceRange ImageSubresourceRange)
{
	VkImageMemoryBarrier ImageMemoryBarrier = VkImageMemoryBarrier();
	ImageMemoryBarrier.sType = VkStructureType::VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	ImageMemoryBarrier.pNext = nullptr;
	ImageMemoryBarrier.srcQueueFamilyIndex = _GraphicsDevice._GraphicsQueueFamilyIndex;
	ImageMemoryBarrier.dstQueueFamilyIndex = _GraphicsDevice._PresentationQueueFamilyIndex;
	ImageMemoryBarrier.image = Image;
	ImageMemoryBarrier.subresourceRange = ImageSubresourceRange;
	ImageMemoryBarrier.srcAccessMask = SourceAccessMask;
	ImageMemoryBarrier.dstAccessMask = TargetAccessMask;
	ImageMemoryBarrier.oldLayout = OldLayout;
	ImageMemoryBarrier.newLayout = NewLayout;

	vkCmdPipelineBarrier(CommandBuffer, SourceStageFlags, TargetStageFlags, 0, 0, nullptr, 0, nullptr, 1, &ImageMemoryBarrier);
}

void Elysium::Graphics::Rendering::Vulkan::CommandBufferVk::DestroyNativeCommandBuffers()
{
	const PresentationParameters& PresentationParameters = _GraphicsDevice.GetPresentationParameters();
	vkFreeCommandBuffers(_GraphicsDevice._NativeLogicalDeviceHandle, _CommandPool._NativeCommandPoolHandle, _NativeCommandBufferHandles.GetLength(), &_NativeCommandBufferHandles[0]);
}
