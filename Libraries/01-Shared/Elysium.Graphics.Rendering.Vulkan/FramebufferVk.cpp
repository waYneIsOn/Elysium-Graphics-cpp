#include "FrameBufferVk.hpp"

#ifndef ELYSIUM_CORE_DELEGATE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Delegate.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FORMATCONVERTER
#include "FormatConverterVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSDEVICEVK
#include "GraphicsDeviceVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::FrameBufferVk(const GraphicsDeviceVk& GraphicsDevice, const RenderPassVk& RenderPass)
	: _GraphicsDevice(GraphicsDevice), _RenderPass(RenderPass),
	_NativeImages(CreateNativeImages()), _NativeImageMemories(CreateNativeImageMemories()), _NativeImageViews(CreateNativeImageViews()),
	_NativeFramebuffers(CreateNativeFramebuffers())
{
	_GraphicsDevice._Canvas.SizeChanged += Elysium::Core::Delegate<void, const Elysium::Graphics::Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::Bind<Elysium::Graphics::Rendering::Vulkan::FrameBufferVk, &Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::Control_SizeChanged>(*this);
}
Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::~FrameBufferVk()
{
	_GraphicsDevice._Canvas.SizeChanged -= Elysium::Core::Delegate<void, const Elysium::Graphics::Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::Bind<Elysium::Graphics::Rendering::Vulkan::FrameBufferVk, &Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::Control_SizeChanged>(*this);

	DestroyNativeFramebuffers();
	DestroyNativeImageViews();
	DestroyNativeImageMemories();
	DestroyNativeImages();
}

const Elysium::Graphics::Rendering::SurfaceFormat Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::GetSurfaceFormat() const
{
	return FormatConverterVk::Convert(_RenderPass._NativeImageFormat);
}

Elysium::Core::Collections::Template::Array<VkImage> Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::CreateNativeImages()
{
	const VkExtent2D& Extent = _GraphicsDevice._NativeSurfaceCapabilities.currentExtent;
	const size_t Length = _GraphicsDevice._BackBufferImageViews.GetLength();

	Elysium::Core::Collections::Template::Array<VkImage> Images = Elysium::Core::Collections::Template::Array<VkImage>(Length);
	VkResult Result;
	for (size_t i = 0; i < Length; i++)
	{
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
		ImageCreateInfo.format = _RenderPass._NativeImageFormat;
		ImageCreateInfo.tiling = VkImageTiling::VK_IMAGE_TILING_OPTIMAL;
		ImageCreateInfo.initialLayout = VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;
		ImageCreateInfo.usage = VkImageUsageFlagBits::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
			VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_DST_BIT;
		ImageCreateInfo.samples = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
		ImageCreateInfo.sharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;

		if ((Result = vkCreateImage(_GraphicsDevice._NativeLogicalDeviceHandle, &ImageCreateInfo, nullptr, &Images[i])) != VK_SUCCESS)
		{
			throw ExceptionVk(Result);
		}
	}

	return Images;
}

Elysium::Core::Collections::Template::Array<VkDeviceMemory> Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::CreateNativeImageMemories()
{
	// ToDo: does it make sense to create a single VkDeviceMemory for all images?
	// see https://stackoverflow.com/questions/64632038/how-to-ensure-correct-destruction-of-vkuniquebuffer-and-vkuniquedevicememory
	// "Also, it's pretty much always a bad idea to allocate memory for just one buffer or image"
	const size_t Length = _GraphicsDevice._BackBufferImageViews.GetLength();

	Elysium::Core::Collections::Template::Array<VkDeviceMemory> ImageMemories = Elysium::Core::Collections::Template::Array<VkDeviceMemory>(Length);
	VkResult Result;
	for (size_t i = 0; i < Length; i++)
	{
		VkMemoryRequirements MemoryRequirements;
		vkGetImageMemoryRequirements(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeImages[i], &MemoryRequirements);

		VkPhysicalDeviceMemoryProperties MemoryProperties;
		vkGetPhysicalDeviceMemoryProperties(_GraphicsDevice._PhysicalDevice._NativePhysicalDeviceHandle, &MemoryProperties);

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

		VkResult Result;
		if ((Result = vkAllocateMemory(_GraphicsDevice._NativeLogicalDeviceHandle, &MemoryAllocateInfo, nullptr, &ImageMemories[i])) != VK_SUCCESS)
		{
			throw ExceptionVk(Result);
		}

		if ((Result = vkBindImageMemory(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeImages[i], ImageMemories[i], 0)) != VK_SUCCESS)
		{
			throw ExceptionVk(Result);
		}
	}

	return ImageMemories;
}

Elysium::Core::Collections::Template::Array<VkImageView> Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::CreateNativeImageViews()
{
	const VkExtent2D& Extent = _GraphicsDevice._NativeSurfaceCapabilities.currentExtent;
	const size_t Length = _GraphicsDevice._BackBufferImageViews.GetLength();

	Elysium::Core::Collections::Template::Array<VkImageView> ImageViews = Elysium::Core::Collections::Template::Array<VkImageView>(Length);
	VkResult Result;
	for (size_t i = 0; i < Length; i++)
	{
		VkImageViewCreateInfo ImageViewCreateInfo = VkImageViewCreateInfo();
		ImageViewCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		ImageViewCreateInfo.pNext = nullptr;
		ImageViewCreateInfo.flags = 0;
		ImageViewCreateInfo.image = _NativeImages[i];
		ImageViewCreateInfo.viewType = VkImageViewType::VK_IMAGE_VIEW_TYPE_2D;
		ImageViewCreateInfo.format = _RenderPass._NativeImageFormat;
		ImageViewCreateInfo.components.r = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY;
		ImageViewCreateInfo.components.g = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY;
		ImageViewCreateInfo.components.b = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY;
		ImageViewCreateInfo.components.a = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY;
		ImageViewCreateInfo.subresourceRange.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
		ImageViewCreateInfo.subresourceRange.baseMipLevel = 0;
		ImageViewCreateInfo.subresourceRange.levelCount = 1;
		ImageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
		ImageViewCreateInfo.subresourceRange.layerCount = 1;

		if ((Result = vkCreateImageView(_GraphicsDevice._NativeLogicalDeviceHandle, &ImageViewCreateInfo, nullptr, &ImageViews[i])) != VK_SUCCESS)
		{
			throw ExceptionVk(Result);
		}
	}

	return ImageViews;
}

Elysium::Core::Collections::Template::Array<VkFramebuffer> Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::CreateNativeFramebuffers()
{
	const VkExtent2D& Extent = _GraphicsDevice._NativeSurfaceCapabilities.currentExtent;
	const size_t Length = _GraphicsDevice._BackBufferImageViews.GetLength();

	Elysium::Core::Collections::Template::Array<VkFramebuffer> Framebuffers = Elysium::Core::Collections::Template::Array<VkFramebuffer>(Length);
	VkResult Result;
	for (size_t i = 0; i < Length; i++)
	{
		const VkImageView Attachments[] = { _NativeImageViews[i] };

		VkFramebufferCreateInfo FramebufferCreateInfo = VkFramebufferCreateInfo();
		FramebufferCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		FramebufferCreateInfo.pNext = nullptr;
		FramebufferCreateInfo.flags = 0;
		FramebufferCreateInfo.renderPass = _RenderPass._NativeRenderPassHandle;
		FramebufferCreateInfo.attachmentCount = 1;
		FramebufferCreateInfo.pAttachments = &Attachments[0];
		FramebufferCreateInfo.width = Extent.width;
		FramebufferCreateInfo.height = Extent.height;
		FramebufferCreateInfo.layers = 1;

		if ((Result = vkCreateFramebuffer(_GraphicsDevice._NativeLogicalDeviceHandle, &FramebufferCreateInfo, nullptr, &Framebuffers[i])) != VK_SUCCESS)
		{
			throw ExceptionVk(Result);
		}
	}

	return Framebuffers;
}

void Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::DestroyNativeFramebuffers()
{
	for (size_t i = 0; i < _NativeFramebuffers.GetLength(); i++)
	{
		if (_NativeFramebuffers[i] != VK_NULL_HANDLE)
		{
			vkDestroyFramebuffer(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeFramebuffers[i], nullptr);
			_NativeFramebuffers[i] = VK_NULL_HANDLE;
		}
	}
}

void Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::DestroyNativeImageViews()
{
	for (size_t i = 0; i < _NativeImageViews.GetLength(); i++)
	{
		if (_NativeImageViews[i] != VK_NULL_HANDLE)
		{
			vkDestroyImageView(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeImageViews[i], nullptr);
			_NativeImageViews[i] = VK_NULL_HANDLE;
		}
	}
}

void Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::DestroyNativeImageMemories()
{
	for (size_t i = 0; i < _NativeImageMemories.GetLength(); i++)
	{
		if (_NativeImageMemories[i] != VK_NULL_HANDLE)
		{
			vkFreeMemory(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeImageMemories[i], nullptr);
			_NativeImageMemories[i] = VK_NULL_HANDLE;
		}
	}
}

void Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::DestroyNativeImages()
{
	for (size_t i = 0; i < _NativeImages.GetLength(); i++)
	{
		if (_NativeImages[i] != VK_NULL_HANDLE)
		{
			vkDestroyImage(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeImages[i], nullptr);
			_NativeImages[i] = VK_NULL_HANDLE;
		}
	}
}

void Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::Control_SizeChanged(const Elysium::Graphics::Presentation::Control& Sender, const Elysium::Core::int32_t Width, const Elysium::Core::int32_t Height)
{
	DestroyNativeFramebuffers();
	DestroyNativeImageViews();
	DestroyNativeImageMemories();
	DestroyNativeImages();

	_NativeImages = CreateNativeImages();
	_NativeImageMemories = CreateNativeImageMemories();
	_NativeImageViews = CreateNativeImageViews();
	_NativeFramebuffers = CreateNativeFramebuffers();
}
