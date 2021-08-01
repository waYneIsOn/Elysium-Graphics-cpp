#include "ShaderVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::ShaderVk::ShaderVk(const LogicalDeviceVk& LogicalDevice)
	: _LogicalDevice(LogicalDevice), _NativeShaderModule(CreateShaderModule())
{ }
Elysium::Graphics::Rendering::Vulkan::ShaderVk::~ShaderVk()
{
	if (_NativeShaderModule != VK_NULL_HANDLE)
	{
		vkDestroyShaderModule(_LogicalDevice._NativeLogicalDeviceHandle, _NativeShaderModule, nullptr);
		_NativeShaderModule = VK_NULL_HANDLE;
	}
}

VkShaderModule Elysium::Graphics::Rendering::Vulkan::ShaderVk::CreateShaderModule()
{
	VkShaderModuleCreateInfo CreateInfo = VkShaderModuleCreateInfo();
	CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	//CreateInfo.codeSize = code.size();
	//CreateInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	VkResult Result;
	VkShaderModule NativeShaderModule;
	if ((Result = vkCreateShaderModule(_LogicalDevice._NativeLogicalDeviceHandle, &CreateInfo, nullptr, &NativeShaderModule)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	return NativeShaderModule;
}
