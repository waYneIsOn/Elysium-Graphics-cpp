#include "GraphicsDeviceVk.hpp"

#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/ArgumentException.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FORMATCONVERTERVK
#include "FormatConverterVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSPIPELINEVK
#include "GraphicsPipelineVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INDEXBUFFERVK
#include "IndexBufferVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SHADERMODULEVK
#include "ShaderModuleVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_VERTEXBUFFERVK
#include "VertexBufferVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GraphicsDeviceVk(const GraphicsInstanceVk& GraphicsInstance, const PhysicalDeviceVk& PhysicalDevice, PresentationParametersVk& PresentationParameters)
	: _GraphicsInstance(GraphicsInstance), _PhysicalDevice(PhysicalDevice), _Canvas(PresentationParameters._Canvas),
	_PresentationParameters(PresentationParameters),
	_NativeSurfaceHandle(CreateNativeSurface()), _NativeSurfaceCapabilities(RetrieveNativeSurfaceCapabilities()),
	_SelectedNativeSurfaceFormat(SelectNativeSurfaceFormat()),
	_GraphicsQueueFamilyIndex(RetrieveGraphicsQueueFamilyIndex()), _PresentationQueueFamilyIndex(RetrievePresentationQueueFamilyIndex()),
	_NativeLogicalDeviceHandle(CreateNativeLogicalDevice()), _GraphicsQueue(*this, _GraphicsQueueFamilyIndex, 0), 
	_PresentationQueue(*this, _PresentationQueueFamilyIndex, 0),
	_NativeSwapchainHandle(CreateNativeSwapchain(VK_NULL_HANDLE)), _CurrentBackBufferImageIndex(0),
	_BackBufferImages(RetrieveNativeBackBufferImages()), _BackBufferImageViews(CreateNativeBackBufferImageViews()),
	_NativeDepthImageHandle(CreateNativeDepthImage()), _NativeDepthImageMemoryHandle(CreateNativeDepthImageMemory()),
	_NativeDepthImageViewHandle(CreateNativeDepthImageView()),
	_RenderFence(*this, true), _PresentationSemaphore(*this), _RenderSemaphore(*this)
{ }
Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::~GraphicsDeviceVk()
{
	// wait for pending operations before destroying any object
	Wait();

	_RenderSemaphore.DestroyNativeSemaphore();
	_PresentationSemaphore.DestroyNativeSemaphore();
	_RenderFence.DestroyNativeFence();

	DestroyNativeDepthImageView();
	DestroyNativeDepthImageMemory();
	DestroyNativeDepthImage();
	DestroyNativeBackBufferImageViews();
	DestroyNativeBackBufferImages();
	DestroyNativeSwapchain(_NativeSwapchainHandle);
	DestroyNativeLogicalDevice();
	DestroyNativeSurface();
}

const Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetPresentationParameters() const
{
	return _PresentationParameters;
}

const Elysium::Graphics::Rendering::SurfaceFormat Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetBackBufferFormat() const
{
	return FormatConverterVk::ToSurfaceFormat(_SelectedNativeSurfaceFormat.format);
}

const Elysium::Graphics::Rendering::Vulkan::FenceVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetRenderFence() const
{
	return _RenderFence;
}

const Elysium::Graphics::Rendering::Vulkan::SemaphoreVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetPresentationSemaphore() const
{
	return _PresentationSemaphore;
}

const Elysium::Graphics::Rendering::Vulkan::SemaphoreVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetRenderSemaphore() const
{
	return _RenderSemaphore;
}

Elysium::Graphics::Rendering::Vulkan::QueueVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetGraphicsQueue()
{
	return _GraphicsQueue;
}

Elysium::Graphics::Rendering::Vulkan::QueueVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetPresentationQueue()
{
	return _PresentationQueue;
}

Elysium::Graphics::Rendering::Native::INativeRenderPass* Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateRenderPass(const SurfaceFormat SurfaceFormat)
{
	return new RenderPassVk(*this, SurfaceFormat);
}

Elysium::Graphics::Rendering::Native::INativeFrameBuffer* Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateFrameBuffer(const Elysium::Graphics::Rendering::Native::INativeRenderPass& RenderPass)
{
	const RenderPassVk& VkRenderPass = reinterpret_cast<const RenderPassVk&>(RenderPass);

	return new FrameBufferVk(*this, VkRenderPass);
}

Elysium::Graphics::Rendering::Native::INativeGraphicsPipeline* Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateGraphicsPipeline()
{
	return new GraphicsPipelineVk(*this);
}

Elysium::Graphics::Rendering::Native::INativeVertexBuffer* Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateVertexBuffer(const VertexDeclaration& Declaration, const Elysium::Core::uint32_t VertexCount, const BufferUsage Usage)
{
	return new VertexBufferVk(*this, Declaration, VertexCount, Usage);
}

Elysium::Graphics::Rendering::Native::INativeIndexBuffer* Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateIndexBuffer(const IndexElementSize ElementSize, const Elysium::Core::uint32_t IndexCount, const BufferUsage Usage)
{
	return new IndexBufferVk(*this, ElementSize, IndexCount, Usage);
}

Elysium::Graphics::Rendering::Native::INativeShaderModule* Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateShaderModule(const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& ByteCode)
{
	return new ShaderModuleVk(*this, ByteCode);
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::Wait() const
{
	VkResult Result;
	if ((Result = vkDeviceWaitIdle(_NativeLogicalDeviceHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}

const bool Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::BeginDraw(Native::INativeFence& RenderFence, const Native::INativeSemaphore& PresentationSemaphore)
{
	const SemaphoreVk& VkPresentSemaphore = dynamic_cast<const SemaphoreVk&>(PresentationSemaphore);

	RenderFence.Wait(Elysium::Core::UInt64::GetMaxValue());
	RenderFence.Reset();

	// aquire next backbuffer image
	VkResult Result;
	if ((Result = vkAcquireNextImageKHR(_NativeLogicalDeviceHandle, _NativeSwapchainHandle, Elysium::Core::UInt64::GetMaxValue(),
		VkPresentSemaphore._NativeSemaphoreHandle, nullptr, &_CurrentBackBufferImageIndex)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	return true;
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::EndDraw(const Native::INativeSemaphore& RenderSemaphore, const Native::INativeQueue& PresentationQueue)
{
	// present current backbuffer image
	const SemaphoreVk& VkRenderSemaphore = dynamic_cast<const SemaphoreVk&>(RenderSemaphore);
	const QueueVk& VkQueue = dynamic_cast<const QueueVk&>(PresentationQueue);

	VkPresentInfoKHR PresentInfo = VkPresentInfoKHR();
	PresentInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	PresentInfo.pNext = nullptr;
	PresentInfo.pImageIndices = &_CurrentBackBufferImageIndex;
	PresentInfo.pResults = nullptr;
	PresentInfo.pSwapchains = &_NativeSwapchainHandle;
	PresentInfo.swapchainCount = 1;
	PresentInfo.pWaitSemaphores = &VkRenderSemaphore._NativeSemaphoreHandle;
	PresentInfo.waitSemaphoreCount = 1;

	VkResult Result;
	if ((Result = vkQueuePresentKHR(VkQueue._NativeQueueHandle, &PresentInfo)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	_CurrentBackBufferImageIndex = (_CurrentBackBufferImageIndex + 1) % _BackBufferImages.GetLength();
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::RecreateResources()
{
	// wait for pending operations
	Wait();

	// retrieve surface values again as some might have changed (for instance width and height)
	_NativeSurfaceCapabilities = RetrieveNativeSurfaceCapabilities();
	_SelectedNativeSurfaceFormat = SelectNativeSurfaceFormat();

	// recreate all required resources
	DestroyNativeDepthImageView();
	DestroyNativeDepthImageMemory();
	DestroyNativeDepthImage();
	DestroyNativeBackBufferImages();
	DestroyNativeBackBufferImageViews();

	VkSwapchainKHR NativeSwapchainHandle = CreateNativeSwapchain(_NativeSwapchainHandle);
	DestroyNativeSwapchain(_NativeSwapchainHandle);
	_NativeSwapchainHandle = NativeSwapchainHandle;
	_BackBufferImages = RetrieveNativeBackBufferImages();
	_BackBufferImageViews = CreateNativeBackBufferImageViews();
	_NativeDepthImageHandle = CreateNativeDepthImage();
	_NativeDepthImageMemoryHandle = CreateNativeDepthImageMemory();
	_NativeDepthImageViewHandle = CreateNativeDepthImageView();
}

VkSurfaceKHR Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateNativeSurface()
{
	VkSurfaceKHR NativeSurfaceHandle;

#if defined(ELYSIUM_CORE_OS_WINDOWS)
	VkWin32SurfaceCreateInfoKHR SurfaceCreateInfo = VkWin32SurfaceCreateInfoKHR();
	SurfaceCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	SurfaceCreateInfo.pNext = nullptr;
	SurfaceCreateInfo.flags = 0;
	SurfaceCreateInfo.hwnd = (HWND)_PresentationParameters._Canvas.GetHandle();
	SurfaceCreateInfo.hinstance = GetModuleHandle(nullptr);

	VkResult Result;
	if ((Result = vkCreateWin32SurfaceKHR(_GraphicsInstance._NativeInstanceHandle, &SurfaceCreateInfo, nullptr, &NativeSurfaceHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
#elif defined(ELYSIUM_CORE_OS_ANDROID)

#elif defined(ELYSIUM_CORE_OS_LINUX)

#elif defined(ELYSIUM_CORE_OS_MAC)

#else
#error "unsupported os"
#endif

	return NativeSurfaceHandle;
}

VkSurfaceCapabilitiesKHR Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::RetrieveNativeSurfaceCapabilities()
{
	VkResult Result;
	VkSurfaceCapabilitiesKHR SurfaceCapabilities;
	if ((Result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &SurfaceCapabilities)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	return SurfaceCapabilities;
}

VkSurfaceFormatKHR Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::SelectNativeSurfaceFormat()
{
	VkResult Result;
	Elysium::Core::uint32_t SurfaceFormatCount;
	if ((Result = vkGetPhysicalDeviceSurfaceFormatsKHR(_PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &SurfaceFormatCount, nullptr)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	Elysium::Core::Collections::Template::Array<VkSurfaceFormatKHR> SurfaceFormats =
		Elysium::Core::Collections::Template::Array<VkSurfaceFormatKHR>(SurfaceFormatCount);
	if ((Result = vkGetPhysicalDeviceSurfaceFormatsKHR(_PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &SurfaceFormatCount, &SurfaceFormats[0])) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	const VkFormat DesiredSurfaceFormat = FormatConverterVk::Convert(_PresentationParameters._DesiredSurfaceFormat);
	const VkColorSpaceKHR DesiredColorSpace = VkColorSpaceKHR::VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;

	VkSurfaceFormatKHR SurfaceFormat = SurfaceFormats[0];
	for (size_t i = 0; i < SurfaceFormats.GetLength(); i++)
	{
		if (SurfaceFormats[i].format == DesiredSurfaceFormat && SurfaceFormats[i].colorSpace == DesiredColorSpace)
		{
			SurfaceFormat = SurfaceFormats[i];
			break;
		}
	}
	
	return SurfaceFormat;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::RetrieveGraphicsQueueFamilyIndex()
{
	Elysium::Core::uint32_t Result = -1;
	const Elysium::Core::Collections::Template::Array<QueueFamilyPropertyVk> QueueFamilyProperties = _PhysicalDevice.GetQueueFamilyProperties();
	for (size_t i = 0; i < QueueFamilyProperties.GetLength(); i++)
	{
		QueueCapabilitiesVk Capabilities = QueueFamilyProperties[i].GetSupportedOperations();
		if ((Capabilities & QueueCapabilitiesVk::Graphics) == QueueCapabilitiesVk::Graphics)
		{
			Result = i;
			break;
		}
	}

	return Result;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::RetrievePresentationQueueFamilyIndex()
{
	Elysium::Core::uint32_t Result = -1;
	const Elysium::Core::Collections::Template::Array<QueueFamilyPropertyVk> QueueFamilyProperties = _PhysicalDevice.GetQueueFamilyProperties();
	for (size_t i = 0; i < QueueFamilyProperties.GetLength(); i++)
	{
		QueueCapabilitiesVk Capabilities = QueueFamilyProperties[i].GetSupportedOperations();
		if ((Capabilities & QueueCapabilitiesVk::Graphics) == QueueCapabilitiesVk::Graphics)
		{
			if (_PhysicalDevice.SupportsPresentation(_NativeSurfaceHandle, i))
			{
				Result = i;
				break;
			}
		}
	}

	return Result;
}


VkDevice Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateNativeLogicalDevice()
{
	// check for queue familys to be used (in this case we're looking for graphics capabilities only) and create a logical device as well as queues required
	const Elysium::Core::Collections::Template::Array<QueueFamilyPropertyVk> QueueFamilyProperties = _PhysicalDevice.GetQueueFamilyProperties();
	const float Priority = 1.0f;
	Elysium::Core::Collections::Template::List<VkDeviceQueueCreateInfo> QueueCreateInfos = Elysium::Core::Collections::Template::List<VkDeviceQueueCreateInfo>();
	for (size_t i = 0; i < QueueFamilyProperties.GetLength(); i++)
	{
		QueueCapabilitiesVk Capabilities = QueueFamilyProperties[i].GetSupportedOperations();
		if ((Capabilities & QueueCapabilitiesVk::Graphics) == QueueCapabilitiesVk::Graphics)
		{
			VkDeviceQueueCreateInfo QueueCreateInfo = VkDeviceQueueCreateInfo();
			QueueCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			QueueCreateInfo.pNext = nullptr;
			QueueCreateInfo.flags = 0;
			QueueCreateInfo.queueFamilyIndex = QueueFamilyProperties[i].GetIndex();
			QueueCreateInfo.queueCount = 1;
			QueueCreateInfo.pQueuePriorities = &Priority;

			QueueCreateInfos.Add(QueueCreateInfo);
		}
	}

	const size_t QueueCreateInfosCount = QueueCreateInfos.GetCount();
	if (QueueCreateInfosCount == 0)
	{
		throw Elysium::Core::InvalidOperationException(u8"Request at least one queue.");
	}

	VkDeviceCreateInfo DeviceCreateInfo = VkDeviceCreateInfo();
	DeviceCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	DeviceCreateInfo.pQueueCreateInfos = &QueueCreateInfos[0];
	DeviceCreateInfo.queueCreateInfoCount = QueueCreateInfosCount;
	DeviceCreateInfo.pEnabledFeatures = &_PhysicalDevice._Features._NativeFeatures;
	if (_PresentationParameters._DeviceExtensionPropertyNames.GetCount() > 0)
	{
		DeviceCreateInfo.ppEnabledExtensionNames = &_PresentationParameters._DeviceExtensionPropertyNames[0];
		DeviceCreateInfo.enabledExtensionCount = _PresentationParameters._DeviceExtensionPropertyNames.GetCount();
	}
	else
	{
		DeviceCreateInfo.ppEnabledExtensionNames = nullptr;
		DeviceCreateInfo.enabledExtensionCount = 0;
	}
	//DeviceCreateInfo.ppEnabledLayerNames = &PresentationParameters._LayerPropertyNames[0];
	//DeviceCreateInfo.enabledLayerCount = PresentationParameters._LayerPropertyNames.GetCount();
	DeviceCreateInfo.ppEnabledLayerNames = nullptr;
	DeviceCreateInfo.enabledLayerCount = 0;
	DeviceCreateInfo.pNext = nullptr;

	VkResult Result;
	VkDevice NativeDeviceHandle;
	if ((Result = vkCreateDevice(_PhysicalDevice._NativePhysicalDeviceHandle, &DeviceCreateInfo, nullptr, &NativeDeviceHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	return NativeDeviceHandle;
}

VkSwapchainKHR Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateNativeSwapchain(const VkSwapchainKHR PreviousNativeSwapchainHandle)
{
	Elysium::Core::uint32_t BackBufferCount = _PresentationParameters.GetBackBufferCount();
	if (BackBufferCount < _NativeSurfaceCapabilities.minImageCount)
	{
		BackBufferCount = _NativeSurfaceCapabilities.minImageCount;
	}
	if (BackBufferCount > _NativeSurfaceCapabilities.maxImageCount)
	{
		BackBufferCount = _NativeSurfaceCapabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR CreateInfo = VkSwapchainCreateInfoKHR();
	CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	CreateInfo.pNext = nullptr;
	CreateInfo.flags = 0;
	CreateInfo.surface = _NativeSurfaceHandle;
	CreateInfo.minImageCount = BackBufferCount;
	CreateInfo.imageFormat = _SelectedNativeSurfaceFormat.format;
	CreateInfo.imageColorSpace = _SelectedNativeSurfaceFormat.colorSpace;
	CreateInfo.imageExtent = _NativeSurfaceCapabilities.currentExtent;
	CreateInfo.imageArrayLayers = 1;
	CreateInfo.imageUsage = VkImageUsageFlagBits::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	CreateInfo.preTransform = _NativeSurfaceCapabilities.currentTransform;
	CreateInfo.compositeAlpha = VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	CreateInfo.presentMode = SelectNativePresentMode();
	CreateInfo.clipped = VK_TRUE;
	CreateInfo.oldSwapchain = PreviousNativeSwapchainHandle;
	if (_GraphicsQueueFamilyIndex != _PresentationQueueFamilyIndex)
	{
		Elysium::Core::uint32_t QueueFamilyIndices[] = { _GraphicsQueueFamilyIndex, _PresentationQueueFamilyIndex };

		CreateInfo.imageSharingMode = VkSharingMode::VK_SHARING_MODE_CONCURRENT;
		CreateInfo.queueFamilyIndexCount = 2;
		CreateInfo.pQueueFamilyIndices = QueueFamilyIndices;
	}
	else
	{
		CreateInfo.imageSharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
		CreateInfo.queueFamilyIndexCount = 0; // Optional
		CreateInfo.pQueueFamilyIndices = nullptr; // Optional
	}

	VkResult Result;
	VkSwapchainKHR NativeSwapchainHandle;
	if ((Result = vkCreateSwapchainKHR(_NativeLogicalDeviceHandle, &CreateInfo, nullptr, &NativeSwapchainHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	return NativeSwapchainHandle;
}

Elysium::Core::Collections::Template::Array<VkImage> Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::RetrieveNativeBackBufferImages()
{
	VkResult Result;
	Elysium::Core::uint32_t BackBufferImageCount = 0;
	if ((Result = vkGetSwapchainImagesKHR(_NativeLogicalDeviceHandle, _NativeSwapchainHandle, &BackBufferImageCount, nullptr)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
	if (BackBufferImageCount == 0)
	{
		// ToDo: throw specific exception
		throw 1;
	}

	Elysium::Core::Collections::Template::Array<VkImage> BackBufferImages = Elysium::Core::Collections::Template::Array<VkImage>(BackBufferImageCount);
	if ((Result = vkGetSwapchainImagesKHR(_NativeLogicalDeviceHandle, _NativeSwapchainHandle, &BackBufferImageCount, &BackBufferImages[0])) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	return BackBufferImages;
}

Elysium::Core::Collections::Template::Array<VkImageView> Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateNativeBackBufferImageViews()
{
	Elysium::Core::uint32_t BackBufferImageCount = _BackBufferImages.GetLength();

	Elysium::Core::Collections::Template::Array<VkImageView> BackBufferImageViews = 
		Elysium::Core::Collections::Template::Array<VkImageView>(BackBufferImageCount);
	for (size_t i = 0; i < BackBufferImageCount; i++)
	{
		VkImageViewCreateInfo ImageViewCreateInfo = VkImageViewCreateInfo();
		ImageViewCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		ImageViewCreateInfo.pNext = nullptr;
		ImageViewCreateInfo.flags = 0;
		ImageViewCreateInfo.image = _BackBufferImages[i];
		ImageViewCreateInfo.viewType = VkImageViewType::VK_IMAGE_VIEW_TYPE_2D;
		ImageViewCreateInfo.format = _SelectedNativeSurfaceFormat.format;
		ImageViewCreateInfo.components.r = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY;
		ImageViewCreateInfo.components.g = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY;
		ImageViewCreateInfo.components.b = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY;
		ImageViewCreateInfo.components.a = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY;
		ImageViewCreateInfo.subresourceRange.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
		ImageViewCreateInfo.subresourceRange.baseMipLevel = 0;
		ImageViewCreateInfo.subresourceRange.levelCount = 1;
		ImageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
		ImageViewCreateInfo.subresourceRange.layerCount = 1;

		VkResult Result;
		if ((Result = vkCreateImageView(_NativeLogicalDeviceHandle, &ImageViewCreateInfo, nullptr, &BackBufferImageViews[i])) != VK_SUCCESS)
		{
			throw ExceptionVk(Result);
		}
	}

	return BackBufferImageViews;
}

VkImage Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateNativeDepthImage()
{
	VkImageCreateInfo ImageCreateInfo = VkImageCreateInfo();
	ImageCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	ImageCreateInfo.pNext = nullptr;
	ImageCreateInfo.flags = 0;
	ImageCreateInfo.imageType = VkImageType::VK_IMAGE_TYPE_2D;
	ImageCreateInfo.extent.width = _NativeSurfaceCapabilities.currentExtent.width;
	ImageCreateInfo.extent.height = _NativeSurfaceCapabilities.currentExtent.height;
	ImageCreateInfo.extent.depth = 1;
	ImageCreateInfo.mipLevels = 1;
	ImageCreateInfo.arrayLayers = 1;
	ImageCreateInfo.format = FormatConverterVk::Convert(_PresentationParameters._DesiredDepthStencilFormat);
	ImageCreateInfo.tiling = VkImageTiling::VK_IMAGE_TILING_OPTIMAL;
	ImageCreateInfo.initialLayout = VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;
	ImageCreateInfo.usage = VkImageUsageFlagBits::VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	ImageCreateInfo.samples = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
	ImageCreateInfo.sharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;

	VkResult Result;
	VkImage DepthImage;
	if ((Result = vkCreateImage(_NativeLogicalDeviceHandle, &ImageCreateInfo, nullptr, &DepthImage)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	return DepthImage;
}

VkDeviceMemory Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateNativeDepthImageMemory()
{
	VkMemoryRequirements MemoryRequirements;
	vkGetImageMemoryRequirements(_NativeLogicalDeviceHandle, _NativeDepthImageHandle, &MemoryRequirements);

	Elysium::Core::uint32_t MemoryTypeIndex = -1;
	for (uint32_t i = 0; i < _PhysicalDevice._NativeMemoryProperties.memoryTypeCount; i++)
	{
		if ((MemoryRequirements.memoryTypeBits & (1 << i)) &&
			(_PhysicalDevice._NativeMemoryProperties.memoryTypes[i].propertyFlags & VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) == VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
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
	VkDeviceMemory DepthImageMemory;
	if ((Result = vkAllocateMemory(_NativeLogicalDeviceHandle, &MemoryAllocateInfo, nullptr, &DepthImageMemory)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	if ((Result = vkBindImageMemory(_NativeLogicalDeviceHandle, _NativeDepthImageHandle, DepthImageMemory, 0)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	return DepthImageMemory;
}

VkImageView Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::CreateNativeDepthImageView()
{
	VkImageViewCreateInfo ImageViewCreateInfo = VkImageViewCreateInfo();
	ImageViewCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	ImageViewCreateInfo.pNext = nullptr;
	ImageViewCreateInfo.flags = 0;
	ImageViewCreateInfo.image = _NativeDepthImageHandle;
	ImageViewCreateInfo.viewType = VkImageViewType::VK_IMAGE_VIEW_TYPE_2D;
	ImageViewCreateInfo.format = FormatConverterVk::Convert(_PresentationParameters._DesiredDepthStencilFormat);
	ImageViewCreateInfo.subresourceRange.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_DEPTH_BIT;
	ImageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
	ImageViewCreateInfo.subresourceRange.baseMipLevel = 0;
	ImageViewCreateInfo.subresourceRange.layerCount = 1;
	ImageViewCreateInfo.subresourceRange.levelCount = 1;
	ImageViewCreateInfo.components.r = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_R;
	ImageViewCreateInfo.components.g = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_G;
	ImageViewCreateInfo.components.b = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_B;
	ImageViewCreateInfo.components.a = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_A;

	VkResult Result;
	VkImageView DepthImageView;
	if ((Result = vkCreateImageView(_NativeLogicalDeviceHandle, &ImageViewCreateInfo, nullptr, &DepthImageView)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	return DepthImageView;
}

VkPresentModeKHR Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::SelectNativePresentMode()
{
	VkResult Result;
	Elysium::Core::uint32_t PresentModeCount;
	if ((Result = vkGetPhysicalDeviceSurfacePresentModesKHR(_PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &PresentModeCount, nullptr)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	Elysium::Core::Collections::Template::Array<VkPresentModeKHR> PresentModes =
		Elysium::Core::Collections::Template::Array<VkPresentModeKHR>(PresentModeCount);
	if ((Result = vkGetPhysicalDeviceSurfacePresentModesKHR(_PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &PresentModeCount, &PresentModes[0])) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	const VkPresentModeKHR DesiredPresentMode = FormatConverterVk::Convert(_PresentationParameters._PresentMode);

	VkPresentModeKHR PresentMode = PresentModes[0];
	for (size_t i = 0; i < PresentModes.GetLength(); i++)
	{
		if (PresentModes[i] == DesiredPresentMode)
		{
			PresentMode = PresentModes[i];
			break;
		}
	}

	return PresentMode;
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::DestroyNativeDepthImageView()
{
	if (_NativeDepthImageViewHandle != VK_NULL_HANDLE)
	{
		vkDestroyImageView(_NativeLogicalDeviceHandle, _NativeDepthImageViewHandle, nullptr);
		_NativeDepthImageViewHandle = VK_NULL_HANDLE;
	}
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::DestroyNativeDepthImageMemory()
{
	if (_NativeDepthImageMemoryHandle != VK_NULL_HANDLE)
	{
		vkFreeMemory(_NativeLogicalDeviceHandle, _NativeDepthImageMemoryHandle, nullptr);
		_NativeDepthImageMemoryHandle = VK_NULL_HANDLE;
	}
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::DestroyNativeDepthImage()
{
	if (_NativeDepthImageHandle != VK_NULL_HANDLE)
	{
		vkDestroyImage(_NativeLogicalDeviceHandle, _NativeDepthImageHandle, nullptr);
		_NativeDepthImageHandle = VK_NULL_HANDLE;
	}
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::DestroyNativeBackBufferImageViews()
{
	for (size_t i = 0; i < _BackBufferImageViews.GetLength(); i++)
	{
		if (_BackBufferImageViews[i] != VK_NULL_HANDLE)
		{
			vkDestroyImageView(_NativeLogicalDeviceHandle, _BackBufferImageViews[i], nullptr);
			_BackBufferImageViews[i] = VK_NULL_HANDLE;
		}
	}
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::DestroyNativeBackBufferImages()
{
	for (size_t i = 0; i < _BackBufferImages.GetLength(); i++)
	{
		if (_BackBufferImages[i] != VK_NULL_HANDLE)
		{
			//vkDestroyImage(_NativeLogicalDeviceHandle, _BackBufferImages[i], nullptr);
			_BackBufferImages[i] = VK_NULL_HANDLE;
		}
	}
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::DestroyNativeSwapchain(VkSwapchainKHR NativeSwapchainHandle)
{
	if (NativeSwapchainHandle != VK_NULL_HANDLE)
	{
		vkDestroySwapchainKHR(_NativeLogicalDeviceHandle, NativeSwapchainHandle, nullptr);
		NativeSwapchainHandle = VK_NULL_HANDLE;
	}
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::DestroyNativeLogicalDevice()
{
	if (_NativeLogicalDeviceHandle != VK_NULL_HANDLE)
	{
		vkDestroyDevice(_NativeLogicalDeviceHandle, nullptr);
		_NativeLogicalDeviceHandle = VK_NULL_HANDLE;
	}
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::DestroyNativeSurface()
{
	if (_NativeSurfaceHandle != VK_NULL_HANDLE)
	{
		vkDestroySurfaceKHR(_GraphicsInstance._NativeInstanceHandle, _NativeSurfaceHandle, nullptr);
		_NativeSurfaceHandle = VK_NULL_HANDLE;
	}
}
