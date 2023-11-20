#include "FrameBufferVk.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Delegate.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FORMATCONVERTERVK
#include "FormatConverterVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSDEVICEVK
#include "GraphicsDeviceVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::FrameBufferVk(const GraphicsDeviceVk& GraphicsDevice, const RenderPassVk& RenderPass)
	: _GraphicsDevice(GraphicsDevice), _RenderPass(RenderPass), _Extent(RetrieveExtent()),
	_NativeImages(CreateNativeImages()), _NativeImageMemory(CreateNativeImageMemory()), _NativeImageViews(CreateNativeImageViews()),
	_NativeFramebuffers(CreateNativeFramebuffers())
{
	_GraphicsDevice._Canvas.SizeChanged += Elysium::Core::Template::Container::Delegate<void, const Elysium::Graphics::Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::Bind<Elysium::Graphics::Rendering::Vulkan::FrameBufferVk, &Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::Control_SizeChanged>(*this);
}

Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::~FrameBufferVk()
{
	_GraphicsDevice._Canvas.SizeChanged -= Elysium::Core::Template::Container::Delegate<void, const Elysium::Graphics::Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::Bind<Elysium::Graphics::Rendering::Vulkan::FrameBufferVk, &Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::Control_SizeChanged>(*this);

	DestroyNativeFramebuffers();
	DestroyNativeImageViews();
	DestroyNativeImageMemory();
	DestroyNativeImages();
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::GetWidth() const
{
	return _Extent.width;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::GetHeight() const
{
	return _Extent.height;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::GetDepth() const
{
	return _Extent.depth;
}

VkExtent3D Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::RetrieveExtent()
{
	const VkExtent2D& Extent = _GraphicsDevice._NativeSurfaceCapabilities.currentExtent;
	const Elysium::Core::uint32_t RenderResolution = _GraphicsDevice._PresentationParameters.GetRenderResolution();

	VkExtent3D Result = VkExtent3D();
	Result.width = Extent.width * RenderResolution / 100.0f;
	Result.height = Extent.height * RenderResolution / 100.0f;
	Result.depth = 1;

	return Result;
}

Elysium::Core::Template::Container::Vector<VkImage> Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::CreateNativeImages()
{
	const size_t Length = _GraphicsDevice._BackBufferImageViews.GetLength();

	Elysium::Core::Template::Container::Vector<VkImage> Images = Elysium::Core::Template::Container::Vector<VkImage>(Length);
	VkResult Result;
	for (size_t i = 0; i < Length; i++)
	{
		VkImageCreateInfo ImageCreateInfo = VkImageCreateInfo();
		ImageCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		ImageCreateInfo.pNext = nullptr;
		ImageCreateInfo.flags = 0;
		ImageCreateInfo.imageType = VkImageType::VK_IMAGE_TYPE_2D;
		ImageCreateInfo.extent = _Extent;
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

VkDeviceMemory Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::CreateNativeImageMemory()
{
	const size_t Length = _GraphicsDevice._BackBufferImageViews.GetLength();

	Elysium::Core::Template::Container::Vector<VkMemoryRequirements> MemoryRequirements =
		Elysium::Core::Template::Container::Vector<VkMemoryRequirements>(Length);

	size_t TotallyRequiredSize = 0;
	Elysium::Core::uint32_t MemoryTypeIndex = -1;

	for (size_t i = 0; i < Length; i++)
	{
		vkGetImageMemoryRequirements(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeImages[i], &MemoryRequirements[i]);

		for (uint32_t j = 0; j < _GraphicsDevice._PhysicalDevice._NativeMemoryProperties.memoryTypeCount; j++)
		{
			if ((MemoryRequirements[i].memoryTypeBits & (1 << j)) &&
				(_GraphicsDevice._PhysicalDevice._NativeMemoryProperties.memoryTypes[j].propertyFlags & VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) == VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
			{
				MemoryTypeIndex = j;
				break;
			}
		}

		TotallyRequiredSize += MemoryRequirements[i].size;
	}
	
	VkMemoryAllocateInfo MemoryAllocateInfo = VkMemoryAllocateInfo();
	MemoryAllocateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	MemoryAllocateInfo.pNext = nullptr;
	MemoryAllocateInfo.allocationSize = TotallyRequiredSize;
	MemoryAllocateInfo.memoryTypeIndex = MemoryTypeIndex;

	VkDeviceMemory ImageMemory;
	VkResult Result;
	if ((Result = vkAllocateMemory(_GraphicsDevice._NativeLogicalDeviceHandle, &MemoryAllocateInfo, nullptr, &ImageMemory)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	size_t Offset = 0;
	for (size_t i = 0; i < Length; i++)
	{
		if ((Result = vkBindImageMemory(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeImages[i], ImageMemory, Offset)) != VK_SUCCESS)
		{
			throw ExceptionVk(Result);
		}

		Offset += MemoryRequirements[i].size;
	}
	
	return ImageMemory;
}

Elysium::Core::Template::Container::Vector<VkImageView> Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::CreateNativeImageViews()
{
	const VkExtent2D& Extent = _GraphicsDevice._NativeSurfaceCapabilities.currentExtent;
	const size_t Length = _GraphicsDevice._BackBufferImageViews.GetLength();

	Elysium::Core::Template::Container::Vector<VkImageView> ImageViews = Elysium::Core::Template::Container::Vector<VkImageView>(Length);
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

Elysium::Core::Template::Container::Vector<VkFramebuffer> Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::CreateNativeFramebuffers()
{
	const size_t Length = _GraphicsDevice._BackBufferImageViews.GetLength();

	Elysium::Core::Template::Container::Vector<VkFramebuffer> Framebuffers = Elysium::Core::Template::Container::Vector<VkFramebuffer>(Length);
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
		FramebufferCreateInfo.width = _Extent.width;
		FramebufferCreateInfo.height = _Extent.height;
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

void Elysium::Graphics::Rendering::Vulkan::FrameBufferVk::DestroyNativeImageMemory()
{
	if (_NativeImageMemory != VK_NULL_HANDLE)
	{
		vkFreeMemory(_GraphicsDevice._NativeLogicalDeviceHandle, _NativeImageMemory, nullptr);
		_NativeImageMemory = VK_NULL_HANDLE;
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
	DestroyNativeImageMemory();
	DestroyNativeImages();

	_Extent = RetrieveExtent();
	_NativeImages = CreateNativeImages();
	_NativeImageMemory = CreateNativeImageMemory();
	_NativeImageViews = CreateNativeImageViews();
	_NativeFramebuffers = CreateNativeFramebuffers();
}
