#include "VertexBufferVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FORMATCONVERTERVK
#include "FormatConverterVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSDEVICEVK
#include "GraphicsDeviceVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::VertexBufferVk::VertexBufferVk(const GraphicsDeviceVk& GraphicsDevice, const VertexDeclaration& Declaration, const Elysium::Core::uint32_t VertexCount, const BufferUsage Usage)
	: _GraphicsDevice(GraphicsDevice), _Declaration(Declaration), _VertexCount(VertexCount), _Usage(Usage),
	_NativeVertexBuffer(CreateNativeVertexBuffer()), _NativeVertexBufferMemory(CreateNativeVertexBufferMemory())
{ }
Elysium::Graphics::Rendering::Vulkan::VertexBufferVk::~VertexBufferVk()
{
	DestroyNativeVertexBufferMemory();
	DestroyNativeVertexBuffer();
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

#ifndef ELYSIUM_GRAPHICS_RENDERING_VERTEXPOSITIONCOLOR
#include "../Elysium.Graphics/VertexPositionColor.hpp"
#endif

void Elysium::Graphics::Rendering::Vulkan::VertexBufferVk::SetData(const IVertexType* First, const size_t Length)
{
	VkResult Result;
	const size_t ByteLength = _Declaration.GetVertexStride() * Length;
	void* Data;
	if ((Result = vkMapMemory(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeVertexBufferMemory, 0, ByteLength, 0, &Data)) != VK_NULL_HANDLE)
	{
		throw ExceptionVk(Result);
	}






	// ToDo: cannot be done when class is derived from IVertexType due to virtual table etc.
	const IVertexType& Test = *First;
	const VertexPositionColor& Test2 = (VertexPositionColor&)Test;
	const size_t Test3 = sizeof(VertexPositionColor);	// is 24, should be 16 (3 floats for position, 1 uint32_t for color)

	std::memcpy(Data, First, ByteLength);






	vkUnmapMemory(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeVertexBufferMemory);
}

VkBuffer Elysium::Graphics::Rendering::Vulkan::VertexBufferVk::CreateNativeVertexBuffer()
{
	VkBufferCreateInfo BufferCreateInfo = VkBufferCreateInfo();
	BufferCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	BufferCreateInfo.pNext = nullptr;
	BufferCreateInfo.flags = 0;
	BufferCreateInfo.usage = VkBufferUsageFlagBits::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	BufferCreateInfo.sharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
	BufferCreateInfo.size = _Declaration.GetVertexStride() * static_cast<const size_t>(_VertexCount);
	// ToDo:
	//BufferCreateInfo.queueFamilyIndexCount = 
	//BufferCreateInfo.pQueueFamilyIndices
	BufferCreateInfo.queueFamilyIndexCount = 0;
	BufferCreateInfo.pQueueFamilyIndices = nullptr;

	VkResult Result;
	VkBuffer Buffer;
	if ((Result = vkCreateBuffer(_GraphicsDevice._NativeLogicalDeviceHandle, &BufferCreateInfo, nullptr, &Buffer)) != VK_NULL_HANDLE)
	{
		throw ExceptionVk(Result);
	}

	return Buffer;
}

VkDeviceMemory Elysium::Graphics::Rendering::Vulkan::VertexBufferVk::CreateNativeVertexBufferMemory()
{
	VkMemoryRequirements MemoryRequirements;
	vkGetBufferMemoryRequirements(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeVertexBuffer, &MemoryRequirements);

	Elysium::Core::uint32_t MemoryTypeIndex = -1;
	VkMemoryPropertyFlags Properties = VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
		VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
	for (Elysium::Core::uint32_t i = 0; i < _GraphicsDevice._PhysicalDevice._NativeMemoryProperties.memoryTypeCount; i++)
	{
		if ((MemoryRequirements.memoryTypeBits & (1 << i)) && (_GraphicsDevice._PhysicalDevice._NativeMemoryProperties.memoryTypes[i].propertyFlags & Properties) == Properties)
		{
			MemoryTypeIndex = i;
			break;
		}
	}

	VkMemoryAllocateInfo MemoryAllocateInfo = VkMemoryAllocateInfo();
	MemoryAllocateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	MemoryAllocateInfo.allocationSize = MemoryRequirements.size;
	MemoryAllocateInfo.memoryTypeIndex = MemoryTypeIndex;

	VkResult Result;
	VkDeviceMemory VertexBufferMemory;
	if ((Result = vkAllocateMemory(_GraphicsDevice._NativeLogicalDeviceHandle, &MemoryAllocateInfo, nullptr, &VertexBufferMemory)) != VK_NULL_HANDLE)
	{
		throw ExceptionVk(Result);
	}

	if ((Result = vkBindBufferMemory(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeVertexBuffer, VertexBufferMemory, 0)))
	{
		throw ExceptionVk(Result);
	}
	
	return VertexBufferMemory;
}

void Elysium::Graphics::Rendering::Vulkan::VertexBufferVk::DestroyNativeVertexBufferMemory()
{
	if (_NativeVertexBufferMemory != VK_NULL_HANDLE)
	{
		vkFreeMemory(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeVertexBufferMemory, nullptr);
		_NativeVertexBufferMemory = VK_NULL_HANDLE;
	}
}

void Elysium::Graphics::Rendering::Vulkan::VertexBufferVk::DestroyNativeVertexBuffer()
{
	if (_NativeVertexBuffer != VK_NULL_HANDLE)
	{
		vkDestroyBuffer(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeVertexBuffer, nullptr);
		_NativeVertexBuffer = VK_NULL_HANDLE;
	}
}
