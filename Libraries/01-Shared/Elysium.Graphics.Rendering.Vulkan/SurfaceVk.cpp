#include "SurfaceVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSINSTANCEVK
#include "GraphicsInstanceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICEVK
#include "PhysicalDeviceVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::SurfaceVk::SurfaceVk(const GraphicsInstanceVk& GraphicsInstance, PresentationParametersVk& PresentationParameters)
	: _NativeInstanceHandle(GraphicsInstance._NativeInstanceHandle),
	_NativeSurfaceHandle(CreateNativeSurface(PresentationParameters))
{
	PresentationParameters.SetSurfaceHandle(*this);

	const Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk& SelectedPhysicalDevice = 
		static_cast<const Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk&>(PresentationParameters.GetGraphicsDevice());

	const SurfaceCapabilitiesVk SurfaceCapabilities = GetCapabilities(SelectedPhysicalDevice);
	const Elysium::Core::Collections::Template::Array<SurfaceFormatVk> AvailableSurfaceFormats = GetFormats(SelectedPhysicalDevice);
	const Elysium::Core::Collections::Template::Array<PresentModeVk> AvailablePresentModes = GetPresentModes(SelectedPhysicalDevice);

	PresentationParameters.SetTransform(SurfaceCapabilities.GetCurrentTransform());
	if (PresentationParameters.GetBackBufferCount() > SurfaceCapabilities.GetMaxImageCount())
	{
		PresentationParameters.SetBackBufferCount(SurfaceCapabilities.GetMaxImageCount());
	}
	PresentationParameters.SetExtent(SurfaceCapabilities.GetMaxImageExtent().Width, SurfaceCapabilities.GetMaxImageExtent().Height);

	PresentationParameters.SetSurfaceFormat(AvailableSurfaceFormats[0]);
	for (size_t i = 0; i < AvailableSurfaceFormats.GetLength(); i++)
	{
		if (AvailableSurfaceFormats[i].Format == FormatVk::B8G8R8A8_SRGB && AvailableSurfaceFormats[i].ColorSpace == ColorSpaceVk::SRGBNonLinear)
		{
			PresentationParameters.SetSurfaceFormat(AvailableSurfaceFormats[i]);
			break;
		}
	}

	PresentationParameters.SetPresentMode(PresentModeVk::Immediate);
	for (size_t i = 0; i < AvailablePresentModes.GetLength(); i++)
	{
		if (AvailablePresentModes[i] == PresentModeVk::Mailbox)
		{
			PresentationParameters.SetPresentMode(AvailablePresentModes[i]);
			break;
		}
	}

	// check for queue familys to be used (in this case we're looking for graphics capabilities only) and create a logical device as well as queues required
	const Elysium::Core::Collections::Template::Array<QueueFamilyPropertyVk> QueueFamilyProperties = SelectedPhysicalDevice.GetQueueFamilyProperties();
	for (size_t i = 0; i < QueueFamilyProperties.GetLength(); i++)
	{
		QueueCapabilitiesVk Capabilities = QueueFamilyProperties[i].GetSupportedOperations();

		if ((Capabilities & QueueCapabilitiesVk::Graphics) == QueueCapabilitiesVk::Graphics)
		{
			if (PresentationParameters.GetGraphicsQueueFamilyIndex() == -1)
			{
				PresentationParameters.SetGraphicsQueueFamilyIndex(i);
			}
			if (PresentationParameters.GetPresentationQueueFamilyIndex() == -1)
			{
				if (SelectedPhysicalDevice.SupportsPresentation(*this, i))
				{
					PresentationParameters.SetPresentationQueueFamilyIndex(i);
				}
			}

			DeviceQueueCreateInfoVk QueueCreateInfo = DeviceQueueCreateInfoVk();
			QueueCreateInfo.SetFamilyIndex(QueueFamilyProperties[i].GetIndex());
			QueueCreateInfo.AddPriority(1.0f);
			QueueCreateInfo.SetCapabilities(Capabilities);

			PresentationParameters.AddDeviceQueueCreateInfo(std::move(QueueCreateInfo));
		}
	}
}
Elysium::Graphics::Rendering::Vulkan::SurfaceVk::~SurfaceVk()
{
	if (_NativeSurfaceHandle != VK_NULL_HANDLE)
	{
		vkDestroySurfaceKHR(_NativeInstanceHandle, _NativeSurfaceHandle, nullptr);
		_NativeSurfaceHandle = VK_NULL_HANDLE;
	}
}

const Elysium::Graphics::Rendering::Vulkan::SurfaceCapabilitiesVk Elysium::Graphics::Rendering::Vulkan::SurfaceVk::GetCapabilities(const PhysicalDeviceVk& PhysicalDevice)
{
	VkSurfaceCapabilitiesKHR NativeSurfaceCapabilities;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &NativeSurfaceCapabilities);

	return SurfaceCapabilitiesVk(NativeSurfaceCapabilities);
}

const Elysium::Core::Collections::Template::Array<Elysium::Graphics::Rendering::Vulkan::SurfaceFormatVk> Elysium::Graphics::Rendering::Vulkan::SurfaceVk::GetFormats(const PhysicalDeviceVk& PhysicalDevice)
{
	uint32_t SurfaceFormatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &SurfaceFormatCount, nullptr);

	Elysium::Core::Collections::Template::Array<SurfaceFormatVk> SurfaceFormats =
		Elysium::Core::Collections::Template::Array<SurfaceFormatVk>(SurfaceFormatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &SurfaceFormatCount, (VkSurfaceFormatKHR*)&SurfaceFormats[0]);

	return SurfaceFormats;
}

const Elysium::Core::Collections::Template::Array<Elysium::Graphics::Rendering::Vulkan::PresentModeVk> Elysium::Graphics::Rendering::Vulkan::SurfaceVk::GetPresentModes(const Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk& PhysicalDevice)
{
	uint32_t PresentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &PresentModeCount, nullptr);

	Elysium::Core::Collections::Template::Array<PresentModeVk> PresentModes =
		Elysium::Core::Collections::Template::Array<PresentModeVk>(PresentModeCount);
	vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &PresentModeCount, (VkPresentModeKHR*)&PresentModes[0]);

	return PresentModes;
}

VkSurfaceKHR Elysium::Graphics::Rendering::Vulkan::SurfaceVk::CreateNativeSurface(PresentationParametersVk& PresentationParameters)
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	VkWin32SurfaceCreateInfoKHR SurfaceCreateInfo = VkWin32SurfaceCreateInfoKHR();
	SurfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	SurfaceCreateInfo.pNext = nullptr;
	SurfaceCreateInfo.flags = 0;
	SurfaceCreateInfo.hwnd = (HWND)PresentationParameters.GetCanvas().GetHandle();
	SurfaceCreateInfo.hinstance = GetModuleHandle(nullptr);

	VkResult Result;
	VkSurfaceKHR NativeSurfaceHandle;
	if ((Result = vkCreateWin32SurfaceKHR(_NativeInstanceHandle, &SurfaceCreateInfo, nullptr, &NativeSurfaceHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	return NativeSurfaceHandle;
#elif defined(ELYSIUM_CORE_OS_ANDROID)

#elif defined(ELYSIUM_CORE_OS_LINUX)

#elif defined(ELYSIUM_CORE_OS_MAC)

#else
#error "unsupported os"
#endif
}
