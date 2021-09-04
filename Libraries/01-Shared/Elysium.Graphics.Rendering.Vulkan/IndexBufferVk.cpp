#include "IndexBufferVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSDEVICEVK
#include "GraphicsDeviceVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::IndexBufferVk::IndexBufferVk(const GraphicsDeviceVk& GraphicsDevice, const IndexElementSize ElementSize, const Elysium::Core::uint32_t IndexCount, const BufferUsage Usage)
	: _GraphicsDevice(GraphicsDevice), _ElementSize(ElementSize), _IndexCount(IndexCount), _Usage(Usage),
	_NativeIndexBuffer(CreateNativeIndexBuffer()), _NativeIndexBufferMemory(CreateNativeIndexBufferMemory())
{ }
Elysium::Graphics::Rendering::Vulkan::IndexBufferVk::~IndexBufferVk()
{
	DestroyNativeIndexBufferMemory();
	DestroyNativeIndexBuffer();
}

const Elysium::Graphics::Rendering::BufferUsage Elysium::Graphics::Rendering::Vulkan::IndexBufferVk::GetBufferUsage() const
{
	return _Usage;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::IndexBufferVk::GetIndexCount() const
{
	return _IndexCount;
}

const Elysium::Graphics::Rendering::IndexElementSize Elysium::Graphics::Rendering::Vulkan::IndexBufferVk::GetIndexElementSize() const
{
	return _ElementSize;
}

void Elysium::Graphics::Rendering::Vulkan::IndexBufferVk::SetData(const void* First, const size_t Length)
{
	VkResult Result;
	const size_t ByteLength = static_cast<Elysium::Core::uint32_t>(_ElementSize) * static_cast<const size_t>(Length);
	Elysium::Core::byte* Data;
	if ((Result = vkMapMemory(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeIndexBufferMemory, 0, ByteLength, 0, (void**)&Data)) != VK_NULL_HANDLE)
	{
		throw ExceptionVk(Result);
	}

	std::memcpy(Data, First, ByteLength);

	vkUnmapMemory(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeIndexBufferMemory);
}

VkBuffer Elysium::Graphics::Rendering::Vulkan::IndexBufferVk::CreateNativeIndexBuffer()
{
	VkBufferCreateInfo BufferCreateInfo = VkBufferCreateInfo();
	BufferCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	BufferCreateInfo.pNext = nullptr;
	BufferCreateInfo.flags = 0;
	BufferCreateInfo.usage = VkBufferUsageFlagBits::VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
	BufferCreateInfo.sharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
	BufferCreateInfo.size = static_cast<Elysium::Core::uint32_t>(_ElementSize) * static_cast<const size_t>(_IndexCount);
	// ToDo:
	//BufferCreateInfo.queueFamilyIndexCount = 
	//BufferCreateInfo.pQueueFamilyIndices
	BufferCreateInfo.queueFamilyIndexCount = 0;
	BufferCreateInfo.pQueueFamilyIndices = nullptr;

	VkResult Result;
	VkBuffer IndexBuffer;
	if ((Result = vkCreateBuffer(_GraphicsDevice._NativeLogicalDeviceHandle, &BufferCreateInfo, nullptr, &IndexBuffer)) != VK_NULL_HANDLE)
	{
		throw ExceptionVk(Result);
	}

	return IndexBuffer;
}

VkDeviceMemory Elysium::Graphics::Rendering::Vulkan::IndexBufferVk::CreateNativeIndexBufferMemory()
{
	VkMemoryRequirements MemoryRequirements;
	vkGetBufferMemoryRequirements(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeIndexBuffer, &MemoryRequirements);

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
	VkDeviceMemory IndexBufferMemory;
	if ((Result = vkAllocateMemory(_GraphicsDevice._NativeLogicalDeviceHandle, &MemoryAllocateInfo, nullptr, &IndexBufferMemory)) != VK_NULL_HANDLE)
	{
		throw ExceptionVk(Result);
	}

	if ((Result = vkBindBufferMemory(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeIndexBuffer, IndexBufferMemory, 0)))
	{
		throw ExceptionVk(Result);
	}

	return IndexBufferMemory;
}

void Elysium::Graphics::Rendering::Vulkan::IndexBufferVk::DestroyNativeIndexBufferMemory()
{
	if (_NativeIndexBufferMemory != VK_NULL_HANDLE)
	{
		vkFreeMemory(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeIndexBufferMemory, nullptr);
		_NativeIndexBufferMemory = VK_NULL_HANDLE;
	}
}

void Elysium::Graphics::Rendering::Vulkan::IndexBufferVk::DestroyNativeIndexBuffer()
{
	if (_NativeIndexBuffer != VK_NULL_HANDLE)
	{
		vkDestroyBuffer(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeIndexBuffer, nullptr);
		_NativeIndexBuffer = VK_NULL_HANDLE;
	}
}
