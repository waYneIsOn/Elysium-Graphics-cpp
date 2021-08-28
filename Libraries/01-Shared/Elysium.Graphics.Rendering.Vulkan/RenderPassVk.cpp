#include "RenderPassVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FORMATCONVERTER
#include "FormatConverterVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSDEVICEVK
#include "GraphicsDeviceVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::RenderPassVk::RenderPassVk(const GraphicsDeviceVk & GraphicsDevice, const SurfaceFormat SurfaceFormat)
	: _GraphicsDevice(GraphicsDevice), _NativeImageFormat(FormatConverterVk::Convert(SurfaceFormat)), _NativeRenderPassHandle(CreateNativeRenderPass())
{ }
Elysium::Graphics::Rendering::Vulkan::RenderPassVk::~RenderPassVk()
{
	DestroyNativeRenderPass();
}

const Elysium::Graphics::Rendering::SurfaceFormat Elysium::Graphics::Rendering::Vulkan::RenderPassVk::GetSurfaceFormat() const
{
	return FormatConverterVk::Convert(_NativeImageFormat);
}

VkRenderPass Elysium::Graphics::Rendering::Vulkan::RenderPassVk::CreateNativeRenderPass()
{
	VkAttachmentDescription ColorAttachment = VkAttachmentDescription();
	ColorAttachment.flags = 0;
	ColorAttachment.format = _NativeImageFormat;
	ColorAttachment.samples = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
	ColorAttachment.loadOp = VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_CLEAR;
	ColorAttachment.storeOp = VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_STORE;
	ColorAttachment.stencilLoadOp = VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	ColorAttachment.stencilStoreOp = VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE;
	ColorAttachment.initialLayout = VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;
	ColorAttachment.finalLayout = VkImageLayout::VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference ColorAttachmentReference = VkAttachmentReference();
	ColorAttachmentReference.attachment = 0;
	ColorAttachmentReference.layout = VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription Subpass = VkSubpassDescription();
	Subpass.flags = 0;
	Subpass.pipelineBindPoint = VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS;
	Subpass.colorAttachmentCount = 1;
	Subpass.pColorAttachments = &ColorAttachmentReference;
	Subpass.inputAttachmentCount = 0;
	Subpass.pInputAttachments = nullptr;
	Subpass.preserveAttachmentCount = 0;
	Subpass.pPreserveAttachments = nullptr;
	Subpass.pDepthStencilAttachment = nullptr;
	Subpass.pResolveAttachments = nullptr;

	VkRenderPassCreateInfo CreateInfo = VkRenderPassCreateInfo();
	CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	CreateInfo.pNext = nullptr;
	CreateInfo.flags = 0;
	CreateInfo.attachmentCount = 1;
	CreateInfo.pAttachments = &ColorAttachment;
	CreateInfo.subpassCount = 1;
	CreateInfo.pSubpasses = &Subpass;
	CreateInfo.dependencyCount = 0;
	CreateInfo.pDependencies = nullptr;

	VkResult Result;
	VkRenderPass RenderPass;
	if ((Result = vkCreateRenderPass(_GraphicsDevice._NativeLogicalDeviceHandle, &CreateInfo, nullptr, &RenderPass)) != VK_NULL_HANDLE)
	{
		throw ExceptionVk(Result);
	}

	return RenderPass;
	/*
	VkAttachmentDescription2 ColorAttachment = VkAttachmentDescription2();
	ColorAttachment.sType = VkStructureType::VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2;
	ColorAttachment.pNext = nullptr;
	ColorAttachment.flags = 0;
	ColorAttachment.format = (VkFormat&)PresentationParameter.GetSurfaceFormat().Format;
	ColorAttachment.samples = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
	ColorAttachment.loadOp = VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_CLEAR;
	ColorAttachment.storeOp = VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_STORE;
	ColorAttachment.stencilLoadOp = VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	ColorAttachment.stencilStoreOp = VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE;
	ColorAttachment.initialLayout = VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;
	ColorAttachment.finalLayout = VkImageLayout::VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference2 ColorAttachmentReference = VkAttachmentReference2();
	ColorAttachmentReference.sType = VkStructureType::VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2;
	ColorAttachmentReference.pNext = nullptr;
	ColorAttachmentReference.attachment = 0;
	ColorAttachmentReference.layout = VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	ColorAttachmentReference.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT; // ToDo <<<<<<<<<<<<<<<

	VkSubpassDescription2 Subpass = VkSubpassDescription2();
	Subpass.sType = VkStructureType::VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2;
	Subpass.pNext = nullptr;
	Subpass.flags = 0;
	Subpass.pipelineBindPoint = VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS;
	Subpass.colorAttachmentCount = 1;
	Subpass.pColorAttachments = &ColorAttachmentReference;
	// >>>>>
	Subpass.viewMask = 0;
	Subpass.inputAttachmentCount = 0;
	Subpass.pInputAttachments = nullptr;
	Subpass.preserveAttachmentCount = 0;
	Subpass.pPreserveAttachments = nullptr;
	Subpass.pDepthStencilAttachment = nullptr;
	Subpass.pResolveAttachments = nullptr;
	// <<<<<

	VkRenderPassCreateInfo2 CreateInfo = VkRenderPassCreateInfo2();
	CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	CreateInfo.pNext = nullptr;
	CreateInfo.flags = 0;
	CreateInfo.attachmentCount = 1;
	CreateInfo.pAttachments = &ColorAttachment;
	CreateInfo.subpassCount = 1;
	CreateInfo.pSubpasses = &Subpass;
	CreateInfo.correlatedViewMaskCount = 0;
	CreateInfo.pCorrelatedViewMasks = nullptr;
	CreateInfo.dependencyCount = 0;
	CreateInfo.pDependencies = nullptr;

	VkResult Result;
	if ((Result = vkCreateRenderPass2(_LogicalDevice._NativeLogicalDeviceHandle, &CreateInfo, nullptr, &_NativeRenderPassHandle)) != VK_NULL_HANDLE)
	{
		throw ExceptionVk(Result);
	}
	*/
}

void Elysium::Graphics::Rendering::Vulkan::RenderPassVk::DestroyNativeRenderPass()
{
	if (_NativeRenderPassHandle != VK_NULL_HANDLE)
	{
		vkDestroyRenderPass(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeRenderPassHandle, nullptr);
		_NativeRenderPassHandle = VK_NULL_HANDLE;
	}
}
