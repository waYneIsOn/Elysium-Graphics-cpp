#include "GraphicsPipelineVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FORMATCONVERTERVK
#include "FormatConverterVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SHADERMODULEVK
#include "ShaderModuleVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_VERTEXBUFFERVK
#include "VertexBufferVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::GraphicsPipelineVk(const GraphicsDeviceVk& GraphicsDevice)
	: _GraphicsDevice(GraphicsDevice), _RasterizerState(),
	_NativePipelineLayoutHandle(CreatePipelineLayout()), _NativePipelineHandle(VK_NULL_HANDLE),
	_Viewports(), _ScissorRectangles(), _ShaderStages(),

	_InputBindingDescriptions(), _InputAttributeDescriptions(),	_PipelineVertexInputStateCreateInfo(CreateDefaultVertexInputStateCreateInfo()),
	
	_InputAssembly(CreateDefaultInputAssemblyStateCreateInfo()),
	_Multisampling(CreateDefaultMultisampleStateCreateInfo()), _ColorBlendAttachment(CreateDefaultColorBlendAttachment()), 
	_ColorBlend(CreateDefaultColorBlendStateCreateInfo())
{ }
Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::~GraphicsPipelineVk()
{
	DestroyNativePipeline();
	DestroyNativePipelineLayout();
}

Elysium::Graphics::Rendering::RasterizerState& Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::GetRasterizerState()
{
	return _RasterizerState;
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::AddViewport(const Elysium::Core::uint32_t X, const Elysium::Core::uint32_t Y, const Elysium::Core::uint32_t Width, const Elysium::Core::uint32_t Height, const float MinimumDepth, const float MaximumDepth)
{
	VkViewport Viewport = VkViewport();
	Viewport.x = X;
	Viewport.y = Y;
	Viewport.width = Width;
	Viewport.height = Height;
	Viewport.minDepth = MinimumDepth;
	Viewport.maxDepth = MaximumDepth;

	_Viewports.Add(Viewport);
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::ClearViewports()
{
	_Viewports.Clear();
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::AddScissorRectangle(const Elysium::Core::int32_t X, const Elysium::Core::int32_t Y, const Elysium::Core::uint32_t Width, const Elysium::Core::uint32_t Height)
{
	VkRect2D ScissorRectangle = VkRect2D();
	ScissorRectangle.offset = { X, Y };
	ScissorRectangle.extent = { Width, Height };

	_ScissorRectangles.Add(ScissorRectangle);
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::ClearScissorRectangles()
{
	_ScissorRectangles.Clear();
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::AddShaderModule(const Native::INativeShaderModule& ShaderModule, const ShaderModuleType Type)
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

void Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::ClearShaderModules()
{
	_ShaderStages.Clear();
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::SetVertexBuffer(const Native::INativeVertexBuffer& VertexBuffer, const Elysium::Core::uint32_t VertexOffset)
{
	const VertexBufferVk& VkVertexBuffer = static_cast<const VertexBufferVk&>(VertexBuffer);
	const Elysium::Graphics::Rendering::VertexDeclaration& VertexDeclaration = VkVertexBuffer.GetVertexDeclaration();

	_InputBindingDescriptions.Clear();
	_InputAttributeDescriptions.Clear();

	VkVertexInputBindingDescription InputBindingDescription = VkVertexInputBindingDescription();
	InputBindingDescription.binding = 0;
	InputBindingDescription.stride = VertexDeclaration.GetVertexStride();
	InputBindingDescription.inputRate = VkVertexInputRate::VK_VERTEX_INPUT_RATE_VERTEX;
	_InputBindingDescriptions.Add(InputBindingDescription);

	const Elysium::Core::Collections::Template::Array<Elysium::Graphics::Rendering::VertexElement>& VertexElements = VertexDeclaration.GetElements();
	const size_t VertexElementsLength = VertexElements.GetLength();
	Elysium::Core::Collections::Template::Array<VkVertexInputAttributeDescription> InputAttributeDescriptions =
		Elysium::Core::Collections::Template::Array<VkVertexInputAttributeDescription>(VertexElementsLength);
	for (size_t i = 0; i < VertexElementsLength; i++)
	{
		InputAttributeDescriptions[i].location = i;
		InputAttributeDescriptions[i].offset = VertexElements[i].GetOffset();
		InputAttributeDescriptions[i].binding = VertexElements[i].GetUsageIndex();
		InputAttributeDescriptions[i].format = FormatConverterVk::Convert(VertexElements[i].GetFormat());
	}
	_InputAttributeDescriptions.AddRange(&InputAttributeDescriptions[0], InputAttributeDescriptions.GetLength());

	_PipelineVertexInputStateCreateInfo = VkPipelineVertexInputStateCreateInfo();
	_PipelineVertexInputStateCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	_PipelineVertexInputStateCreateInfo.pNext = nullptr;
	_PipelineVertexInputStateCreateInfo.flags = 0;
	_PipelineVertexInputStateCreateInfo.vertexAttributeDescriptionCount = VertexElementsLength;
	_PipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions = VertexElementsLength  == 0 ? nullptr : &_InputAttributeDescriptions[0];
	_PipelineVertexInputStateCreateInfo.vertexBindingDescriptionCount = _InputBindingDescriptions.GetCount();
	_PipelineVertexInputStateCreateInfo.pVertexBindingDescriptions = _PipelineVertexInputStateCreateInfo.vertexBindingDescriptionCount == 0 ?
		nullptr : &_InputBindingDescriptions[0];
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::Build(const Native::INativeRenderPass& RenderPass)
{
	DestroyNativePipeline();

	const RenderPassVk& VkRenderPass = static_cast<const RenderPassVk&>(RenderPass);

	const size_t ViewportCount = _Viewports.GetCount();
	const size_t ScissorRectangleCount = _ScissorRectangles.GetCount();
	if (ViewportCount != ScissorRectangleCount)
	{	// ToDo: throw specific exception
		throw 1;
	}
	const size_t ShaderCount = _ShaderStages.GetCount();

	VkPipelineViewportStateCreateInfo ViewportStateCreateInfo = VkPipelineViewportStateCreateInfo();
	ViewportStateCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	ViewportStateCreateInfo.pNext = nullptr;
	ViewportStateCreateInfo.flags = 0;
	ViewportStateCreateInfo.viewportCount = ViewportCount;
	ViewportStateCreateInfo.pViewports = ViewportCount == 0 ? nullptr : &_Viewports[0];
	ViewportStateCreateInfo.scissorCount = ScissorRectangleCount;
	ViewportStateCreateInfo.pScissors = ScissorRectangleCount == 0 ? nullptr : &_ScissorRectangles[0];

	VkPipelineRasterizationStateCreateInfo PipelineRasterizationStateCreateInfo = VkPipelineRasterizationStateCreateInfo();
	PipelineRasterizationStateCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	PipelineRasterizationStateCreateInfo.pNext = nullptr;
	PipelineRasterizationStateCreateInfo.flags = 0;
	PipelineRasterizationStateCreateInfo.polygonMode = FormatConverterVk::Convert(_RasterizerState.GetFillMode());
	PipelineRasterizationStateCreateInfo.lineWidth = _RasterizerState.GetLineWidth();
	// ToDo: _RasterizerState -> PipelineRasterizationStateCreateInfo
	PipelineRasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
	PipelineRasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
	PipelineRasterizationStateCreateInfo.cullMode = VkCullModeFlagBits::VK_CULL_MODE_NONE;
	PipelineRasterizationStateCreateInfo.frontFace = VkFrontFace::VK_FRONT_FACE_CLOCKWISE;
	PipelineRasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;
	PipelineRasterizationStateCreateInfo.depthBiasClamp = 0.0f;
	PipelineRasterizationStateCreateInfo.depthBiasConstantFactor = 0.0f;
	PipelineRasterizationStateCreateInfo.depthBiasSlopeFactor = 0.0f;

	VkGraphicsPipelineCreateInfo PipelineCreateInfo = VkGraphicsPipelineCreateInfo();
	PipelineCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	PipelineCreateInfo.pNext = nullptr;
	PipelineCreateInfo.flags = 0;
	PipelineCreateInfo.layout = _NativePipelineLayoutHandle;
	PipelineCreateInfo.stageCount = ShaderCount;
	PipelineCreateInfo.pStages = ShaderCount == 0 ? nullptr : &_ShaderStages[0];
	PipelineCreateInfo.pVertexInputState = &_PipelineVertexInputStateCreateInfo;
	PipelineCreateInfo.pInputAssemblyState = &_InputAssembly;
	PipelineCreateInfo.pViewportState = &ViewportStateCreateInfo;
	PipelineCreateInfo.pRasterizationState = &PipelineRasterizationStateCreateInfo;
	PipelineCreateInfo.pMultisampleState = &_Multisampling;
	PipelineCreateInfo.pColorBlendState = &_ColorBlend;
	PipelineCreateInfo.renderPass = VkRenderPass._NativeRenderPassHandle;
	PipelineCreateInfo.subpass = 0;
	PipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;

	VkResult Result;
	if ((Result = vkCreateGraphicsPipelines(_GraphicsDevice._NativeLogicalDeviceHandle, VK_NULL_HANDLE, 1, &PipelineCreateInfo, nullptr, &_NativePipelineHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}

VkPipelineLayout Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::CreatePipelineLayout()
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
	if ((Result = vkCreatePipelineLayout(_GraphicsDevice._NativeLogicalDeviceHandle, &PipelineLayoutCreateInfo, nullptr, &Layout)) != VK_SUCCESS)
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
	CreateInfo.blendConstants[0] = 0.0f;
	CreateInfo.blendConstants[1] = 0.0f;
	CreateInfo.blendConstants[2] = 0.0f;
	CreateInfo.blendConstants[3] = 0.0f;

	return CreateInfo;
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::DestroyNativePipeline()
{
	if (_NativePipelineHandle != VK_NULL_HANDLE)
	{
		vkDestroyPipeline(_GraphicsDevice._NativeLogicalDeviceHandle, _NativePipelineHandle, nullptr);
		_NativePipelineHandle = VK_NULL_HANDLE;
	}
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::DestroyNativePipelineLayout()
{
	if (_NativePipelineLayoutHandle != VK_NULL_HANDLE)
	{
		vkDestroyPipelineLayout(_GraphicsDevice._NativeLogicalDeviceHandle, _NativePipelineLayoutHandle, nullptr);
		_NativePipelineLayoutHandle = VK_NULL_HANDLE;
	}
}
