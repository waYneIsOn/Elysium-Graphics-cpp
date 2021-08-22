#include "ShaderModuleVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::ShaderModuleVk::ShaderModuleVk(const GraphicsDeviceVk& GraphicsDevice, const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& Data)
	: _GraphicsDevice(GraphicsDevice), _NativeShaderModule(CreateShaderModule(&Data[0], Data.GetLength()))
{ }
Elysium::Graphics::Rendering::Vulkan::ShaderModuleVk::~ShaderModuleVk()
{
	if (_NativeShaderModule != VK_NULL_HANDLE)
	{
		vkDestroyShaderModule(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeShaderModule, nullptr);
		_NativeShaderModule = VK_NULL_HANDLE;
	}
}

VkShaderModule Elysium::Graphics::Rendering::Vulkan::ShaderModuleVk::CreateShaderModule(const Elysium::Core::byte* Data, const size_t Length)
{
	VkShaderModuleCreateInfo CreateInfo = VkShaderModuleCreateInfo();
	CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	CreateInfo.codeSize = Length;
	CreateInfo.pCode = reinterpret_cast<const Elysium::Core::uint32_t*>(Data);

	VkResult Result;
	VkShaderModule NativeShaderModule;
	if ((Result = vkCreateShaderModule(_GraphicsDevice._NativeLogicalDeviceHandle, &CreateInfo, nullptr, &NativeShaderModule)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	return NativeShaderModule;
}
