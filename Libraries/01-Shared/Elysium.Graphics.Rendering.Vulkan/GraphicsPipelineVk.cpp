#include "GraphicsPipelineVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SHADERMODULEVK
#include "ShaderModuleVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::GraphicsPipelineVk(const GraphicsDeviceVk& GraphicsDevice)
	: _GraphicsDevice(GraphicsDevice), _NativePipelineLayoutHandle(CreatePipelineLayout()), _ShaderStages(),
	_VertexInputState(CreateDefaultVertexInputStateCreateInfo()), _InputAssembly(CreateDefaultInputAssemblyStateCreateInfo()),
	_Viewport(CreateDefaultViewport()), _ScissorRectangle(CreateDefaultScissorRectangle()),
	_Rasterizer(CreateDefaultRasterizationStateCreateInfo()), _Multisampling(CreateDefaultMultisampleStateCreateInfo()),
	_ColorBlendAttachment(CreateDefaultColorBlendAttachment()), _ColorBlend(CreateDefaultColorBlendStateCreateInfo()),
	_NativePipelineHandle(VK_NULL_HANDLE)
{ }
Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::~GraphicsPipelineVk()
{
	if (_NativePipelineHandle != VK_NULL_HANDLE)
	{
		vkDestroyPipeline(_GraphicsDevice._LogicalDevice._NativeLogicalDeviceHandle, _NativePipelineHandle, nullptr);
	}
	if (_NativePipelineLayoutHandle != VK_NULL_HANDLE)
	{
		vkDestroyPipelineLayout(_GraphicsDevice._LogicalDevice._NativeLogicalDeviceHandle, _NativePipelineLayoutHandle, nullptr);
	}
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::AddShaderModule(const INativeShaderModule& ShaderModule, const ShaderModuleType Type)
{
	const ShaderModuleVk& VkShaderModule = static_cast<const ShaderModuleVk&>(ShaderModule);

	VkPipelineShaderStageCreateInfo ShaderStageCreateInfo = VkPipelineShaderStageCreateInfo();
	ShaderStageCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	ShaderStageCreateInfo.pNext = nullptr;
	ShaderStageCreateInfo.flags = 0;
	ShaderStageCreateInfo.module = VkShaderModule._NativeShaderModule;
	ShaderStageCreateInfo.pName = "main";	// ToDo: do I really want to limit all shader's entrypoint names?
	ShaderStageCreateInfo.pSpecializationInfo = nullptr;
	ShaderStageCreateInfo.stage = (VkShaderStageFlagBits)Type;

	_ShaderStages.Add(ShaderStageCreateInfo);
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::Build(const INativeRenderPass& RenderPass)
{
	const RenderPassVk& VkRenderPass = static_cast<const RenderPassVk&>(RenderPass);

	VkPipelineViewportStateCreateInfo ViewportStateCreateInfo = VkPipelineViewportStateCreateInfo();
	ViewportStateCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	ViewportStateCreateInfo.pNext = nullptr;
	ViewportStateCreateInfo.flags = 0;
	ViewportStateCreateInfo.viewportCount = 1;
	ViewportStateCreateInfo.pViewports = &_Viewport;
	ViewportStateCreateInfo.scissorCount = 1;
	ViewportStateCreateInfo.pScissors = &_ScissorRectangle;

	VkGraphicsPipelineCreateInfo PipelineCreateInfo = VkGraphicsPipelineCreateInfo();
	PipelineCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	PipelineCreateInfo.pNext = nullptr;
	PipelineCreateInfo.flags = 0;
	PipelineCreateInfo.layout = _NativePipelineLayoutHandle;
	PipelineCreateInfo.stageCount = _ShaderStages.GetCount();
	PipelineCreateInfo.pStages = &_ShaderStages[0];
	PipelineCreateInfo.pVertexInputState = &_VertexInputState;
	PipelineCreateInfo.pInputAssemblyState = &_InputAssembly;
	PipelineCreateInfo.pViewportState = &ViewportStateCreateInfo;
	PipelineCreateInfo.pRasterizationState = &_Rasterizer;
	PipelineCreateInfo.pMultisampleState = &_Multisampling;
	PipelineCreateInfo.pColorBlendState = &_ColorBlend;
	PipelineCreateInfo.renderPass = VkRenderPass._NativeRenderPassHandle;
	PipelineCreateInfo.subpass = 0;
	PipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;

	VkResult Result;
	if ((Result = vkCreateGraphicsPipelines(_GraphicsDevice._LogicalDevice._NativeLogicalDeviceHandle, VK_NULL_HANDLE, 1, &PipelineCreateInfo, nullptr, &_NativePipelineHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}

const VkPipelineLayout Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::CreatePipelineLayout()
{
	VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo = VkPipelineLayoutCreateInfo();
	PipelineLayoutCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	PipelineLayoutCreateInfo.pNext = nullptr;
	PipelineLayoutCreateInfo.flags = 0;
	PipelineLayoutCreateInfo.pushConstantRangeCount = 0;
	PipelineLayoutCreateInfo.pPushConstantRanges = nullptr;
	PipelineLayoutCreateInfo.setLayoutCount = 0;
	PipelineLayoutCreateInfo.pSetLayouts = nullptr;

	VkResult Result;
	VkPipelineLayout Layout;
	if ((Result = vkCreatePipelineLayout(_GraphicsDevice._LogicalDevice._NativeLogicalDeviceHandle, &PipelineLayoutCreateInfo, nullptr, &Layout)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	return Layout;
}

VkPipelineVertexInputStateCreateInfo Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::CreateDefaultVertexInputStateCreateInfo()
{
	VkPipelineVertexInputStateCreateInfo CreateInfo = VkPipelineVertexInputStateCreateInfo();
	CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	CreateInfo.pNext = nullptr;
	CreateInfo.flags = 0;
	CreateInfo.vertexAttributeDescriptionCount = 0;
	CreateInfo.pVertexAttributeDescriptions = nullptr;
	CreateInfo.vertexBindingDescriptionCount = 0;
	CreateInfo.pVertexBindingDescriptions = nullptr;

	return CreateInfo;
}

VkPipelineInputAssemblyStateCreateInfo Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::CreateDefaultInputAssemblyStateCreateInfo()
{
	VkPipelineInputAssemblyStateCreateInfo CreateInfo = VkPipelineInputAssemblyStateCreateInfo();
	CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	CreateInfo.pNext = nullptr;
	CreateInfo.flags = 0;
	CreateInfo.primitiveRestartEnable = VK_FALSE;
	CreateInfo.topology = VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

	return CreateInfo;
}

VkViewport Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::CreateDefaultViewport()
{
	Extent2DVk& Extent = _GraphicsDevice._PresentationParameters._Extent;

	VkViewport Viewport = VkViewport();
	Viewport.x = 0.0f;
	Viewport.y = 0.0f;
	Viewport.width = Extent.Width;
	Viewport.height = Extent.Height;
	Viewport.minDepth = 0.0f;
	Viewport.maxDepth = 1.0f;

	return Viewport;
}

VkRect2D Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::CreateDefaultScissorRectangle()
{
	Extent2DVk& Extent = _GraphicsDevice._PresentationParameters._Extent;

	VkRect2D ScissorRectangle = VkRect2D();
	ScissorRectangle.offset = { 0, 0 };
	ScissorRectangle.extent = VkExtent2D();
	ScissorRectangle.extent.width = Extent.Width;
	ScissorRectangle.extent.height = Extent.Height;

	return ScissorRectangle;
}

VkPipelineRasterizationStateCreateInfo Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::CreateDefaultRasterizationStateCreateInfo()
{
	VkPipelineRasterizationStateCreateInfo CreateInfo = VkPipelineRasterizationStateCreateInfo();
	CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	CreateInfo.pNext = nullptr;
	CreateInfo.flags = 0;
	CreateInfo.depthClampEnable = VK_FALSE;
	CreateInfo.rasterizerDiscardEnable = VK_FALSE;
	CreateInfo.cullMode = VkCullModeFlagBits::VK_CULL_MODE_NONE;
	CreateInfo.frontFace = VkFrontFace::VK_FRONT_FACE_CLOCKWISE;
	CreateInfo.depthBiasEnable = VK_FALSE;
	CreateInfo.depthBiasClamp = 0.0f;
	CreateInfo.depthBiasConstantFactor = 0.0f;
	CreateInfo.depthBiasSlopeFactor = 0.0f;
	CreateInfo.lineWidth = 1.0f;
	CreateInfo.polygonMode = VkPolygonMode::VK_POLYGON_MODE_FILL;

	return CreateInfo;
}

VkPipelineMultisampleStateCreateInfo Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::CreateDefaultMultisampleStateCreateInfo()
{
	VkPipelineMultisampleStateCreateInfo CreateInfo = VkPipelineMultisampleStateCreateInfo();
	CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	CreateInfo.pNext = nullptr;
	CreateInfo.flags = 0;
	CreateInfo.sampleShadingEnable = VK_FALSE;
	CreateInfo.rasterizationSamples = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
	CreateInfo.minSampleShading = 1.0f;
	CreateInfo.pSampleMask = nullptr;
	CreateInfo.alphaToCoverageEnable = VK_FALSE;
	CreateInfo.alphaToOneEnable = VK_FALSE;

	return CreateInfo;
}

VkPipelineColorBlendAttachmentState Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::CreateDefaultColorBlendAttachment()
{
	VkPipelineColorBlendAttachmentState ColorBlendAttachment = VkPipelineColorBlendAttachmentState();
	ColorBlendAttachment.colorWriteMask = VkColorComponentFlagBits::VK_COLOR_COMPONENT_R_BIT | VkColorComponentFlagBits::VK_COLOR_COMPONENT_G_BIT |
		VkColorComponentFlagBits::VK_COLOR_COMPONENT_B_BIT | VkColorComponentFlagBits::VK_COLOR_COMPONENT_A_BIT;
	ColorBlendAttachment.blendEnable = VK_FALSE;
	ColorBlendAttachment.dstAlphaBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ZERO;
	ColorBlendAttachment.dstColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ZERO;
	ColorBlendAttachment.srcAlphaBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ZERO;
	ColorBlendAttachment.srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ZERO;
	ColorBlendAttachment.alphaBlendOp = VkBlendOp::VK_BLEND_OP_ADD;
	ColorBlendAttachment.colorBlendOp = VkBlendOp::VK_BLEND_OP_ADD;

	return ColorBlendAttachment;
}

VkPipelineColorBlendStateCreateInfo Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::CreateDefaultColorBlendStateCreateInfo()
{
	VkPipelineColorBlendStateCreateInfo CreateInfo = VkPipelineColorBlendStateCreateInfo();
	CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	CreateInfo.pNext = nullptr;
	CreateInfo.flags = 0;
	CreateInfo.attachmentCount = 1;
	CreateInfo.pAttachments = &_ColorBlendAttachment;
	CreateInfo.logicOpEnable = VK_FALSE;
	CreateInfo.logicOp = VkLogicOp::VK_LOGIC_OP_COPY;
	//CreateInfo.blendConstants = { 0.0f, 0.0f, 0.0f, 0.0f };

	return CreateInfo;
}
