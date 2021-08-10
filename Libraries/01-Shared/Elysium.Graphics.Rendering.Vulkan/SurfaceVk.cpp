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

Elysium::Graphics::Rendering::Vulkan::SurfaceVk::SurfaceVk(const GraphicsInstanceVk& GraphicsInstance, const PhysicalDeviceVk& PhysicalDevice, PresentationParametersVk& PresentationParameters)
	: _NativeInstanceHandle(GraphicsInstance._NativeInstanceHandle), _PhysicalDevice(PhysicalDevice), _Canvas(_PresentationParameters.GetCanvas()), _PresentationParameters(PresentationParameters),
	_NativeSurfaceHandle(CreateNativeSurface()), _NativeSurfaceCapabilities(GetNativeSurfaceCapabilities())
{
	UpdateInternalValues();
	_Canvas.SizeChanged += Elysium::Core::Delegate<void, const Elysium::Graphics::Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::Bind<Elysium::Graphics::Rendering::Vulkan::SurfaceVk, &Elysium::Graphics::Rendering::Vulkan::SurfaceVk::Control_SizeChanged>(*this);
}
Elysium::Graphics::Rendering::Vulkan::SurfaceVk::~SurfaceVk()
{
	_Canvas.SizeChanged -= Elysium::Core::Delegate<void, const Elysium::Graphics::Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::Bind<Elysium::Graphics::Rendering::Vulkan::SurfaceVk, &Elysium::Graphics::Rendering::Vulkan::SurfaceVk::Control_SizeChanged>(*this);
	if (_NativeSurfaceHandle != VK_NULL_HANDLE)
	{
		vkDestroySurfaceKHR(_NativeInstanceHandle, _NativeSurfaceHandle, nullptr);
	}
}

const VkSurfaceKHR Elysium::Graphics::Rendering::Vulkan::SurfaceVk::CreateNativeSurface()
{
	VkSurfaceKHR NativeSurfaceHandle;

#if defined(ELYSIUM_CORE_OS_WINDOWS)
	VkWin32SurfaceCreateInfoKHR SurfaceCreateInfo = VkWin32SurfaceCreateInfoKHR();
	SurfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	SurfaceCreateInfo.pNext = nullptr;
	SurfaceCreateInfo.flags = 0;
	SurfaceCreateInfo.hwnd = (HWND)_Canvas.GetHandle();
	SurfaceCreateInfo.hinstance = GetModuleHandle(nullptr);

	VkResult Result;
	if ((Result = vkCreateWin32SurfaceKHR(_NativeInstanceHandle, &SurfaceCreateInfo, nullptr, &NativeSurfaceHandle)) != VK_SUCCESS)
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

VkSurfaceCapabilitiesKHR Elysium::Graphics::Rendering::Vulkan::SurfaceVk::GetNativeSurfaceCapabilities()
{
	VkSurfaceCapabilitiesKHR SurfaceCapabilities;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &SurfaceCapabilities);

	return SurfaceCapabilities;
}

void Elysium::Graphics::Rendering::Vulkan::SurfaceVk::UpdateInternalValues()
{
	// ...
	_NativeSurfaceCapabilities = GetNativeSurfaceCapabilities();

	_PresentationParameters.SetTransform(_NativeSurfaceCapabilities.currentTransform);
	if (_PresentationParameters.GetBackBufferCount() > _NativeSurfaceCapabilities.maxImageCount)
	{
		_PresentationParameters.SetBackBufferCount(_NativeSurfaceCapabilities.maxImageCount);
	}
	_PresentationParameters.SetExtent(_NativeSurfaceCapabilities.maxImageExtent.width, _NativeSurfaceCapabilities.maxImageExtent.height);

	// ...
	Elysium::Core::uint32_t SurfaceFormatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(_PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &SurfaceFormatCount, nullptr);

	Elysium::Core::Collections::Template::Array<SurfaceFormatVk> SurfaceFormats =
		Elysium::Core::Collections::Template::Array<SurfaceFormatVk>(SurfaceFormatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(_PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &SurfaceFormatCount, (VkSurfaceFormatKHR*)&SurfaceFormats[0]);

	_PresentationParameters.SetSurfaceFormat(SurfaceFormats[0]);
	for (size_t i = 0; i < SurfaceFormats.GetLength(); i++)
	{
		if (SurfaceFormats[i].Format == FormatVk::B8G8R8A8_SRGB && SurfaceFormats[i].ColorSpace == ColorSpaceVk::SRGBNonLinear)
		{
			_PresentationParameters.SetSurfaceFormat(SurfaceFormats[i]);
			break;
		}
	}

	// ...
	Elysium::Core::uint32_t PresentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(_PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &PresentModeCount, nullptr);

	Elysium::Core::Collections::Template::Array<PresentModeVk> PresentModes =
		Elysium::Core::Collections::Template::Array<PresentModeVk>(PresentModeCount);
	vkGetPhysicalDeviceSurfacePresentModesKHR(_PhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &PresentModeCount, (VkPresentModeKHR*)&PresentModes[0]);
	/*
	_PresentationParameters.SetPresentMode(PresentModeVk::Immediate);
	for (size_t i = 0; i < PresentModes.GetLength(); i++)
	{
		if (PresentModes[i] == PresentModeVk::Mailbox)
		{
			_PresentationParameters.SetPresentMode(PresentModes[i]);
			break;
		}
	}
	*/
}

void Elysium::Graphics::Rendering::Vulkan::SurfaceVk::Control_SizeChanged(const Elysium::Graphics::Presentation::Control& Sender, const Elysium::Core::int32_t Width, const Elysium::Core::int32_t Height)
{
	UpdateInternalValues();
	SizeChanged(*this);
}
