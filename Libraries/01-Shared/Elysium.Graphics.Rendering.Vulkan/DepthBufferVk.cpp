#include "DepthBufferVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FORMATCONVERTERT
#include "FormatConverterVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICEVK
#include "PhysicalDeviceVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::DepthBufferVk::DepthBufferVk(SurfaceVk& Surface, const LogicalDeviceVk& LogicalDevice)
	: _Surface(Surface), _LogicalDevice(LogicalDevice), _NativeDepthImageHandle(VK_NULL_HANDLE), _NativeDepthImageMemoryHandle(VK_NULL_HANDLE),
	_NativeDepthImageViewHandle(VK_NULL_HANDLE)
{
	_Surface.SizeChanged += Elysium::Core::Delegate<void, const Elysium::Graphics::Rendering::Vulkan::SurfaceVk&>::CreateDelegate<Elysium::Graphics::Rendering::Vulkan::DepthBufferVk, &Elysium::Graphics::Rendering::Vulkan::DepthBufferVk::Surface_OnSizeChanged>(*this);
	CreateResources();
}
Elysium::Graphics::Rendering::Vulkan::DepthBufferVk::~DepthBufferVk()
{
	_Surface.SizeChanged -= Elysium::Core::Delegate<void, const Elysium::Graphics::Rendering::Vulkan::SurfaceVk&>::CreateDelegate<Elysium::Graphics::Rendering::Vulkan::DepthBufferVk, &Elysium::Graphics::Rendering::Vulkan::DepthBufferVk::Surface_OnSizeChanged>(*this);
	DestroyResources();
}

void Elysium::Graphics::Rendering::Vulkan::DepthBufferVk::DestroyResources()
{
	if (_NativeDepthImageViewHandle != VK_NULL_HANDLE)
	{
		vkDestroyImageView(_LogicalDevice._NativeLogicalDeviceHandle, _NativeDepthImageViewHandle, nullptr);
		_NativeDepthImageViewHandle = VK_NULL_HANDLE;
	}
	if (_NativeDepthImageMemoryHandle != VK_NULL_HANDLE)
	{
		vkFreeMemory(_LogicalDevice._NativeLogicalDeviceHandle, _NativeDepthImageMemoryHandle, nullptr);
		_NativeDepthImageMemoryHandle = VK_NULL_HANDLE;
	}
	if (_NativeDepthImageHandle != VK_NULL_HANDLE)
	{
		vkDestroyImage(_LogicalDevice._NativeLogicalDeviceHandle, _NativeDepthImageHandle, nullptr);
		_NativeDepthImageHandle = VK_NULL_HANDLE;
	}
}

void Elysium::Graphics::Rendering::Vulkan::DepthBufferVk::CreateResources()
{
	const PresentationParametersVk& PresentationParameters = _LogicalDevice.GetPresentationParameters();
	const VkExtent2D& Extent = (const VkExtent2D&)PresentationParameters.GetExtent();
	
	VkResult Result;

	VkImageCreateInfo ImageCreateInfo = VkImageCreateInfo();
	ImageCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	ImageCreateInfo.pNext = nullptr;
	ImageCreateInfo.flags = 0;
	ImageCreateInfo.imageType = VkImageType::VK_IMAGE_TYPE_2D;
	ImageCreateInfo.extent.width = Extent.width;
	ImageCreateInfo.extent.height = Extent.height;
	ImageCreateInfo.extent.depth = 1;
	ImageCreateInfo.mipLevels = 1;
	ImageCreateInfo.arrayLayers = 1;
	ImageCreateInfo.format = FormatConverterVk::Convert(PresentationParameters.GetDesiredDepthFormat());
	ImageCreateInfo.tiling = VkImageTiling::VK_IMAGE_TILING_OPTIMAL;
	ImageCreateInfo.initialLayout = VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;
	ImageCreateInfo.usage = VkImageUsageFlagBits::VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	ImageCreateInfo.samples = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
	ImageCreateInfo.sharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
	if ((Result = vkCreateImage(_LogicalDevice._NativeLogicalDeviceHandle, &ImageCreateInfo, nullptr, &_NativeDepthImageHandle)) != VK_SUCCESS)
	{
		DestroyResources();
		throw ExceptionVk(Result);
	}

	VkMemoryRequirements MemoryRequirements;
	vkGetImageMemoryRequirements(_LogicalDevice._NativeLogicalDeviceHandle, _NativeDepthImageHandle, &MemoryRequirements);
	
	VkPhysicalDeviceMemoryProperties MemoryProperties;
	vkGetPhysicalDeviceMemoryProperties(_LogicalDevice._PhysicalDevice._NativePhysicalDeviceHandle, &MemoryProperties);

	Elysium::Core::uint32_t MemoryTypeIndex = -1;
	for (uint32_t i = 0; i < MemoryProperties.memoryTypeCount; i++)
	{
		if ((MemoryRequirements.memoryTypeBits & (1 << i)) &&
			(MemoryProperties.memoryTypes[i].propertyFlags & VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) == VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
		{
			MemoryTypeIndex = i;
			break;
		}
	}
	
	VkMemoryAllocateInfo MemoryAllocateInfo = VkMemoryAllocateInfo();
	MemoryAllocateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	MemoryAllocateInfo.pNext = nullptr;
	MemoryAllocateInfo.allocationSize = MemoryRequirements.size;
	MemoryAllocateInfo.memoryTypeIndex = MemoryTypeIndex;
	if ((Result = vkAllocateMemory(_LogicalDevice._NativeLogicalDeviceHandle, &MemoryAllocateInfo, nullptr, &_NativeDepthImageMemoryHandle)) != VK_SUCCESS)
	{
		DestroyResources();
		throw ExceptionVk(Result);
	}

	if ((Result = vkBindImageMemory(_LogicalDevice._NativeLogicalDeviceHandle, _NativeDepthImageHandle, _NativeDepthImageMemoryHandle, 0)) != VK_SUCCESS)
	{
		DestroyResources();
		throw ExceptionVk(Result);
	}

	VkImageViewCreateInfo ImageViewCreateInfo = VkImageViewCreateInfo();
	ImageViewCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	ImageViewCreateInfo.pNext = nullptr;
	ImageViewCreateInfo.flags = 0;
	ImageViewCreateInfo.image = _NativeDepthImageHandle;
	ImageViewCreateInfo.viewType = VkImageViewType::VK_IMAGE_VIEW_TYPE_2D;
	ImageViewCreateInfo.format = ImageCreateInfo.format;
	ImageViewCreateInfo.subresourceRange.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_DEPTH_BIT;
	ImageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
	ImageViewCreateInfo.subresourceRange.baseMipLevel = 0;
	ImageViewCreateInfo.subresourceRange.layerCount = 1;
	ImageViewCreateInfo.subresourceRange.levelCount = 1;
	ImageViewCreateInfo.components.r = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_R;
	ImageViewCreateInfo.components.g = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_G;
	ImageViewCreateInfo.components.b = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_B;
	ImageViewCreateInfo.components.a = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_A;
	if ((Result = vkCreateImageView(_LogicalDevice._NativeLogicalDeviceHandle, &ImageViewCreateInfo, nullptr, &_NativeDepthImageViewHandle)) != VK_SUCCESS)
	{
		DestroyResources();
		throw ExceptionVk(Result);
	}
	/*
	// ...
	VkImageSubresourceRange ImageSubresourceRange = VkImageSubresourceRange();
	ImageSubresourceRange.baseArrayLayer = 0;
	ImageSubresourceRange.baseMipLevel = 0;
	ImageSubresourceRange.layerCount = 1;
	ImageSubresourceRange.levelCount = 1;
	ImageSubresourceRange.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;

	VkImageMemoryBarrier ConvertImageLayoutMemoryBarrier = VkImageMemoryBarrier();
	ConvertImageLayoutMemoryBarrier.sType = VkStructureType::VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	ConvertImageLayoutMemoryBarrier.pNext = nullptr;
	ConvertImageLayoutMemoryBarrier.image = _NativeDepthImageHandle;
	ConvertImageLayoutMemoryBarrier.subresourceRange = ImageSubresourceRange;
	ConvertImageLayoutMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	ConvertImageLayoutMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	ConvertImageLayoutMemoryBarrier.srcAccessMask = VkAccessFlagBits::VK_ACCESS_MEMORY_READ_BIT;
	ConvertImageLayoutMemoryBarrier.dstAccessMask = VkAccessFlagBits::VK_ACCESS_TRANSFER_WRITE_BIT;
	ConvertImageLayoutMemoryBarrier.oldLayout = VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;
	ConvertImageLayoutMemoryBarrier.newLayout = VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	vkCmdPipelineBarrier(_NativeCommandBufferHandles[i], VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
		VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0,
		nullptr, 0, nullptr, 1, &ConvertImageLayoutMemoryBarrier);
	*/
}

void Elysium::Graphics::Rendering::Vulkan::DepthBufferVk::RecreateDepthBuffer()
{
	DestroyResources();
	CreateResources();
}

void Elysium::Graphics::Rendering::Vulkan::DepthBufferVk::Surface_OnSizeChanged(const Elysium::Graphics::Rendering::Vulkan::SurfaceVk & Sender)
{
	RecreateDepthBuffer();
}
