#include "VertexBufferVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSDEVICEVK
#include "GraphicsDeviceVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::VertexBufferVk::VertexBufferVk(const GraphicsDeviceVk& GraphicsDevice, const VertexDeclaration& Declaration, const Elysium::Core::uint32_t VertexCount, const BufferUsage Usage)
	: _GraphicsDevice(GraphicsDevice), _Declaration(Declaration), _VertexCount(VertexCount), _Usage(Usage),
	_NativeVertexBuffer(VK_NULL_HANDLE)
{
	VkVertexInputBindingDescription InputBindingDescription = VkVertexInputBindingDescription();
	InputBindingDescription.binding = 0;
	InputBindingDescription.stride = _Declaration.GetVertexStride();
	InputBindingDescription.inputRate = VkVertexInputRate::VK_VERTEX_INPUT_RATE_VERTEX;

	//for ()
	{
		VkVertexInputAttributeDescription InputAttributeDescription = VkVertexInputAttributeDescription();
		InputAttributeDescription.binding = 0;
		InputAttributeDescription.location = 0;
		InputAttributeDescription.format = VkFormat::VK_FORMAT_R32G32_SFLOAT;
		//InputAttributeDescription.offset = offsetof(Vertex, pos);
	}

	VkBufferCreateInfo BufferCreateInfo = VkBufferCreateInfo();
	BufferCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	BufferCreateInfo.pNext = nullptr;
	BufferCreateInfo.flags = 0;
	BufferCreateInfo.usage = VkBufferUsageFlagBits::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	BufferCreateInfo.sharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
	//BufferCreateInfo.size = sizeof(vertices[0]) * _VertexCount;
	//BufferCreateInfo.pQueueFamilyIndices
	//BufferCreateInfo.queueFamilyIndexCount

	VkPipelineVertexInputStateCreateInfo PipelineVertexInputStateCreateInfo = VkPipelineVertexInputStateCreateInfo();
	PipelineVertexInputStateCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	PipelineVertexInputStateCreateInfo.pNext = nullptr;
	PipelineVertexInputStateCreateInfo.flags = 0;
	//PipelineVertexInputStateCreateInfo.vertexAttributeDescriptionCount
	//PipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions =
	//PipelineVertexInputStateCreateInfo.vertexBindingDescriptionCount
	//PipelineVertexInputStateCreateInfo.pVertexBindingDescriptions

	VkResult Result;
	if ((Result = vkCreateBuffer(_GraphicsDevice._LogicalDevice._NativeLogicalDeviceHandle, &BufferCreateInfo, nullptr, &_NativeVertexBuffer)) != VK_NULL_HANDLE)
	{
		throw ExceptionVk(Result);
	}

}
Elysium::Graphics::Rendering::Vulkan::VertexBufferVk::~VertexBufferVk()
{
	if (_NativeVertexBuffer != VK_NULL_HANDLE)
	{
		vkDestroyBuffer(_GraphicsDevice._LogicalDevice._NativeLogicalDeviceHandle, _NativeVertexBuffer, nullptr);
		_NativeVertexBuffer = VK_NULL_HANDLE;
	}
}

const Elysium::Graphics::Rendering::BufferUsage Elysium::Graphics::Rendering::Vulkan::VertexBufferVk::GetBufferUsage() const
{
	return _Usage;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::VertexBufferVk::GetVertexCount() const
{
	return _VertexCount;
}

const Elysium::Graphics::Rendering::VertexDeclaration& Elysium::Graphics::Rendering::Vulkan::VertexBufferVk::GetVertexDeclaration() const
{
	return _Declaration;
}
