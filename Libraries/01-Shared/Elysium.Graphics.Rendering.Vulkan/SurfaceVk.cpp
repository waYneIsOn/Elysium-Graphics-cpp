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
	: _NativeInstanceHandle(GraphicsInstance._NativeInstanceHandle), _PresentationParameters(PresentationParameters),
	_NativeSurfaceHandle(CreateNativeSurface(_PresentationParameters))
{
	_PresentationParameters.SetSurfaceHandle(*this);
	UpdateInternalValues();

	Elysium::Graphics::Presentation::Control& Canvas = _PresentationParameters.GetCanvas();
	Canvas.SizeChanged += Elysium::Core::Delegate<void, const Elysium::Graphics::Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::CreateDelegate<Elysium::Graphics::Rendering::Vulkan::SurfaceVk, &Elysium::Graphics::Rendering::Vulkan::SurfaceVk::Control_SizeChanged>(*this);

	// ToDo: this shouldn't be done here
	{
		const Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk& SelectedPhysicalDevice =
			static_cast<const Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk&>(PresentationParameters.GetGraphicsDevice());

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
}
Elysium::Graphics::Rendering::Vulkan::SurfaceVk::~SurfaceVk()
{
	Elysium::Graphics::Presentation::Control& Canvas = _PresentationParameters.GetCanvas();
	Canvas.SizeChanged -= Elysium::Core::Delegate<void, const Elysium::Graphics::Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::CreateDelegate<Elysium::Graphics::Rendering::Vulkan::SurfaceVk, &Elysium::Graphics::Rendering::Vulkan::SurfaceVk::Control_SizeChanged>(*this);

	if (_NativeSurfaceHandle != VK_NULL_HANDLE)
	{
		vkDestroySurfaceKHR(_NativeInstanceHandle, _NativeSurfaceHandle, nullptr);
		_NativeSurfaceHandle = VK_NULL_HANDLE;
	}
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

void Elysium::Graphics::Rendering::Vulkan::SurfaceVk::UpdateInternalValues()
{
	const Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk& SelectedPhysicalDevice =
		static_cast<const Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk&>(_PresentationParameters.GetGraphicsDevice());

	// ...
	VkSurfaceCapabilitiesKHR SurfaceCapabilities;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(SelectedPhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &SurfaceCapabilities);

	_PresentationParameters.SetTransform(SurfaceCapabilities.currentTransform);
	if (_PresentationParameters.GetBackBufferCount() > SurfaceCapabilities.maxImageCount)
	{
		_PresentationParameters.SetBackBufferCount(SurfaceCapabilities.maxImageCount);
	}
	_PresentationParameters.SetExtent(SurfaceCapabilities.maxImageExtent.width, SurfaceCapabilities.maxImageExtent.height);

	// ...
	Elysium::Core::uint32_t SurfaceFormatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(SelectedPhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &SurfaceFormatCount, nullptr);

	Elysium::Core::Collections::Template::Array<SurfaceFormatVk> SurfaceFormats =
		Elysium::Core::Collections::Template::Array<SurfaceFormatVk>(SurfaceFormatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(SelectedPhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &SurfaceFormatCount, (VkSurfaceFormatKHR*)&SurfaceFormats[0]);

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
	vkGetPhysicalDeviceSurfacePresentModesKHR(SelectedPhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &PresentModeCount, nullptr);

	Elysium::Core::Collections::Template::Array<PresentModeVk> PresentModes =
		Elysium::Core::Collections::Template::Array<PresentModeVk>(PresentModeCount);
	vkGetPhysicalDeviceSurfacePresentModesKHR(SelectedPhysicalDevice._NativePhysicalDeviceHandle, _NativeSurfaceHandle, &PresentModeCount, (VkPresentModeKHR*)&PresentModes[0]);

	_PresentationParameters.SetPresentMode(PresentModeVk::Immediate);
	for (size_t i = 0; i < PresentModes.GetLength(); i++)
	{
		if (PresentModes[i] == PresentModeVk::Mailbox)
		{
			_PresentationParameters.SetPresentMode(PresentModes[i]);
			break;
		}
	}
}

void Elysium::Graphics::Rendering::Vulkan::SurfaceVk::Control_SizeChanged(const Elysium::Graphics::Presentation::Control& Sender, const Elysium::Core::int32_t Width, const Elysium::Core::int32_t Height)
{
	UpdateInternalValues();
	SizeChanged(*this);
}
