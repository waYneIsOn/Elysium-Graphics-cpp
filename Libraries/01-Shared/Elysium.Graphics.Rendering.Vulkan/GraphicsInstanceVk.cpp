#include "GraphicsInstanceVk.hpp"

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_APINOTAVAILABLEEXCEPTION
#include "../Elysium.Graphics/APINotAvailableException.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICEVK
#include "PhysicalDeviceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PRESENTATIONPARAMETERSVK
#include "PresentationParametersVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::GraphicsInstanceVk::GraphicsInstanceVk()
{ }
Elysium::Graphics::Rendering::Vulkan::GraphicsInstanceVk::~GraphicsInstanceVk()
{
	if (_NativeInstanceHandle != VK_NULL_HANDLE)
	{
		vkDestroyInstance(_NativeInstanceHandle, nullptr);
	}
}

const Elysium::Core::Collections::Template::Array<Elysium::Graphics::Rendering::Vulkan::ExtensionPropertyVk> Elysium::Graphics::Rendering::Vulkan::GraphicsInstanceVk::GetAvailableExtensions()
{
	VkResult Result;

	Elysium::Core::uint32_t ExtensionCount = 0;
	if ((Result = vkEnumerateInstanceExtensionProperties(nullptr, &ExtensionCount, nullptr)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	Elysium::Core::Collections::Template::Array<VkExtensionProperties> ExtensionProperties = 
		Elysium::Core::Collections::Template::Array<VkExtensionProperties>(ExtensionCount);
	if ((Result = vkEnumerateInstanceExtensionProperties(nullptr, &ExtensionCount, &ExtensionProperties[0])) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	Elysium::Core::Collections::Template::Array<ExtensionPropertyVk> WrappedExtensionProperties =
		Elysium::Core::Collections::Template::Array<ExtensionPropertyVk>(ExtensionCount);
	for (size_t i = 0; i < ExtensionCount; i++)
	{
		WrappedExtensionProperties[i]._NativeProperty = ExtensionProperties[i];
	}
	
	return WrappedExtensionProperties;
}

const Elysium::Core::Collections::Template::Array<Elysium::Graphics::Rendering::Vulkan::LayerPropertyVk> Elysium::Graphics::Rendering::Vulkan::GraphicsInstanceVk::GetAvailableLayers()
{
	VkResult Result;

	Elysium::Core::uint32_t LayerCount = 0;
	if ((Result = vkEnumerateInstanceLayerProperties(&LayerCount, nullptr)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	Elysium::Core::Collections::Template::Array<VkLayerProperties> LayerProperties =
		Elysium::Core::Collections::Template::Array<VkLayerProperties>(LayerCount);
	if ((Result = vkEnumerateInstanceLayerProperties(&LayerCount, &LayerProperties[0])) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	Elysium::Core::Collections::Template::Array<LayerPropertyVk> WrappedLayerProperties =
		Elysium::Core::Collections::Template::Array<LayerPropertyVk>(LayerCount);
	for (size_t i = 0; i < LayerCount; i++)
	{
		WrappedLayerProperties[i]._NativeProperty = LayerProperties[i];
	}

	return WrappedLayerProperties;
}

const Elysium::Core::Collections::Template::Array<Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk> Elysium::Graphics::Rendering::Vulkan::GraphicsInstanceVk::GetPhysicalGraphicsDevices()
{
	if (_NativeInstanceHandle == VK_NULL_HANDLE)
	{
		throw Elysium::Core::InvalidOperationException(u8"Physical graphics devices can only be retrieved after initialization.");
	}

	VkResult Result;

	Elysium::Core::uint32_t DeviceCount = 0;
	if ((Result = vkEnumeratePhysicalDevices(_NativeInstanceHandle, &DeviceCount, nullptr)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	Elysium::Core::Collections::Template::Array<VkPhysicalDevice> Devices =
		Elysium::Core::Collections::Template::Array<VkPhysicalDevice>(DeviceCount);
	if ((Result = vkEnumeratePhysicalDevices(_NativeInstanceHandle, &DeviceCount, &Devices[0])) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	Elysium::Core::Collections::Template::Array<PhysicalDeviceVk> PhysicalGraphicsDevices = Elysium::Core::Collections::Template::Array<PhysicalDeviceVk>(DeviceCount);
	for (size_t i = 0; i < DeviceCount; i++)
	{
		PhysicalGraphicsDevices[i]._NativePhysicalDeviceHandle = Devices[i];
		vkGetPhysicalDeviceProperties(PhysicalGraphicsDevices[i]._NativePhysicalDeviceHandle, &PhysicalGraphicsDevices[i]._Properties._NativeProperties);
		vkGetPhysicalDeviceFeatures(PhysicalGraphicsDevices[i]._NativePhysicalDeviceHandle, &PhysicalGraphicsDevices[i]._Features._NativeFeatures);

		// ToDo:
		//vkGetPhysicalDeviceFormatProperties()
		//vkGetPhysicalDeviceImageFormatProperties()
		//vkGetPhysicalDeviceQueueFamilyProperties()
		//vkGetPhysicalDeviceMemoryProperties()
		// etc.
	}

	return PhysicalGraphicsDevices;
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsInstanceVk::Initialize(const PresentationParametersVk & PresentationParameters)
{
	const Core::Collections::Template::List<char*> ExtensionProperties = PresentationParameters._ExtensionPropertyNames;
	const Core::Collections::Template::List<char*> LayerProperties = PresentationParameters._LayerPropertyNames;

	VkApplicationInfo ApplicationInfo = VkApplicationInfo();
	ApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	ApplicationInfo.apiVersion = VK_API_VERSION_1_0;
	ApplicationInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
	ApplicationInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
	ApplicationInfo.pApplicationName = (const char*)&PresentationParameters.GetApplicationName()[0];
	ApplicationInfo.pEngineName = (const char*)u8"Elysium Graphics";
	ApplicationInfo.pNext = nullptr;

	VkInstanceCreateInfo InstanceCreateInfo = VkInstanceCreateInfo();
	InstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	InstanceCreateInfo.pApplicationInfo = &ApplicationInfo;
	InstanceCreateInfo.enabledExtensionCount = ExtensionProperties.GetCount();
	InstanceCreateInfo.enabledLayerCount = LayerProperties.GetCount();
	if (InstanceCreateInfo.enabledExtensionCount > 0)
	{
		InstanceCreateInfo.ppEnabledExtensionNames = &ExtensionProperties[0];
	}
	if (InstanceCreateInfo.enabledLayerCount > 0)
	{
		InstanceCreateInfo.ppEnabledLayerNames = &LayerProperties[0];
	}
	
	VkResult Result;
	if ((Result = vkCreateInstance(&InstanceCreateInfo, nullptr, &_NativeInstanceHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}

Elysium::Graphics::Rendering::Vulkan::SurfaceVk Elysium::Graphics::Rendering::Vulkan::GraphicsInstanceVk::CreateSurface(const PresentationParametersVk& PresentationParameters)
{
	VkResult Result;

#if defined(ELYSIUM_CORE_OS_WINDOWS)
	VkWin32SurfaceCreateInfoKHR SurfaceCreateInfo = VkWin32SurfaceCreateInfoKHR();
	SurfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	SurfaceCreateInfo.hwnd = (HWND)PresentationParameters.GetCanvas().GetHandle();
	SurfaceCreateInfo.hinstance = GetModuleHandle(nullptr);

	VkSurfaceKHR NativeSurfaceHandle;
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

	return SurfaceVk(_NativeInstanceHandle, NativeSurfaceHandle);
}
