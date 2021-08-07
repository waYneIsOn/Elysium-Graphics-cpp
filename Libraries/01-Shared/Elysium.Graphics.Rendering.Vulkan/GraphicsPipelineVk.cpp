#include "GraphicsPipelineVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SHADERMODULEVK
#include "ShaderModuleVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::GraphicsPipelineVk(const GraphicsDeviceVk& GraphicsDevice)
	: _GraphicsDevice(GraphicsDevice), _NativePipelineHandle(VK_NULL_HANDLE), _NativePipelineLayoutHandle(VK_NULL_HANDLE)
{ }
Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::~GraphicsPipelineVk()
{
	if (_NativePipelineHandle != VK_NULL_HANDLE)
	{
		vkDestroyPipeline(_GraphicsDevice._LogicalDevice._NativeLogicalDeviceHandle, _NativePipelineHandle, nullptr);
	}
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::AddShaderModule(const INativeShaderModule& ShaderModule)
{
	const ShaderModuleVk& VkShaderModule = static_cast<const ShaderModuleVk&>(ShaderModule);

	throw 1;
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsPipelineVk::Build()
{
	VkGraphicsPipelineCreateInfo PipelineCreateInfo = VkGraphicsPipelineCreateInfo();
	PipelineCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	PipelineCreateInfo.pNext = nullptr;
	PipelineCreateInfo.flags = 0;
	/*
	PipelineCreateInfo.stageCount = _shaderStages.size();
	PipelineCreateInfo.pStages = _shaderStages.data();
	PipelineCreateInfo.pVertexInputState = &_vertexInputInfo;
	PipelineCreateInfo.pInputAssemblyState = &_inputAssembly;
	PipelineCreateInfo.pViewportState = &viewportState;
	PipelineCreateInfo.pRasterizationState = &_rasterizer;
	PipelineCreateInfo.pMultisampleState = &_multisampling;
	PipelineCreateInfo.pColorBlendState = &colorBlending;
	PipelineCreateInfo.layout = _pipelineLayout;
	PipelineCreateInfo.renderPass = pass;
	PipelineCreateInfo.subpass = 0;
	PipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
	*/


	/*
	VkResult Result;
	if ((Result = vkCreateGraphicsPipelines(_NativePhysicalDeviceHandle, nullptr, &ExtensionCount, (VkExtensionProperties*)&Extensions[0])) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
	*/
	throw 1;
}
