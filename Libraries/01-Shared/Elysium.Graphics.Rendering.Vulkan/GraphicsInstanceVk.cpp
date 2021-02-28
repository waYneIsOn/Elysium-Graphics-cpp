#include "GraphicsInstanceVk.hpp"

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
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
	: _NativeInstanceHandle(CreateInstance()), _NativeDebugUtilsMessengerHandle(VK_NULL_HANDLE), _PhysicalGraphicsDevices(RetrievePhysicalGraphicsDevices())
{ }
Elysium::Graphics::Rendering::Vulkan::GraphicsInstanceVk::~GraphicsInstanceVk()
{
	DisableDebugging();
	if (_NativeInstanceHandle != VK_NULL_HANDLE)
	{
		vkDestroyInstance(_NativeInstanceHandle, nullptr);
		_NativeInstanceHandle = VK_NULL_HANDLE;
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

	Elysium::Core::Collections::Template::Array<ExtensionPropertyVk> Extensions =
		Elysium::Core::Collections::Template::Array<ExtensionPropertyVk>(ExtensionCount);
	if ((Result = vkEnumerateInstanceExtensionProperties(nullptr, &ExtensionCount, (VkExtensionProperties*)&Extensions[0])) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	return Extensions;
}

const Elysium::Core::Collections::Template::Array<Elysium::Graphics::Rendering::Vulkan::LayerPropertyVk> Elysium::Graphics::Rendering::Vulkan::GraphicsInstanceVk::GetAvailableLayers()
{
	VkResult Result;

	Elysium::Core::uint32_t LayerCount = 0;
	if ((Result = vkEnumerateInstanceLayerProperties(&LayerCount, nullptr)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	Elysium::Core::Collections::Template::Array<LayerPropertyVk> Layers =
		Elysium::Core::Collections::Template::Array<LayerPropertyVk>(LayerCount);
	if ((Result = vkEnumerateInstanceLayerProperties(&LayerCount, (VkLayerProperties*)&Layers[0])) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	return Layers;
}

const Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk& Elysium::Graphics::Rendering::Vulkan::GraphicsInstanceVk::GetPhysicalDevice(const Elysium::Core::uint32_t Index) const
{
	return _PhysicalGraphicsDevices[Index];
}

const Elysium::Core::Collections::Template::Array<Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk>& Elysium::Graphics::Rendering::Vulkan::GraphicsInstanceVk::GetPhysicalGraphicsDevices()
{
	return _PhysicalGraphicsDevices;
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsInstanceVk::EnableDebugging()
{
	VkDebugUtilsMessengerCreateInfoEXT CreateInfo = VkDebugUtilsMessengerCreateInfoEXT();
	CreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	CreateInfo.pNext = nullptr;
	CreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	CreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	CreateInfo.pfnUserCallback = DebugCallback;

	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_NativeInstanceHandle, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr)
	{
		VkResult Result;
		if ((Result = func(_NativeInstanceHandle, &CreateInfo, nullptr, &_NativeDebugUtilsMessengerHandle)) != VK_SUCCESS)
		{
			throw ExceptionVk(Result);
		}
	}
	else
	{	// ToDo: throw specific exception
		throw 1;
	}
}

void Elysium::Graphics::Rendering::Vulkan::GraphicsInstanceVk::DisableDebugging()
{
	if (_NativeDebugUtilsMessengerHandle != VK_NULL_HANDLE)
	{
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_NativeInstanceHandle, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr)
		{
			func(_NativeInstanceHandle, _NativeDebugUtilsMessengerHandle, nullptr);
		}
	}
}

VkInstance Elysium::Graphics::Rendering::Vulkan::GraphicsInstanceVk::CreateInstance()
{
	// ToDo: currently all extensions and layers get added - make this configurable
	const Elysium::Core::Collections::Template::Array<ExtensionPropertyVk> AvailableInstanceExtensions = GraphicsInstanceVk::GetAvailableExtensions();
	const Elysium::Core::Collections::Template::Array<LayerPropertyVk> AvailableLayers = GraphicsInstanceVk::GetAvailableLayers();

	Elysium::Core::Collections::Template::List<char*> ExtensionPropertyNames = Elysium::Core::Collections::Template::List<char*>(0);
	for (size_t i = 0; i < AvailableInstanceExtensions.GetLength(); i++)
	{
		ExtensionPropertyNames.Add((char*)&AvailableInstanceExtensions[i].GetName()[0]);
	}

	Elysium::Core::Collections::Template::List<char*> LayerNames = Elysium::Core::Collections::Template::List<char*>(0);
	for (size_t i = 0; i < AvailableLayers.GetLength(); i++)
	{
		LayerNames.Add((char*)&AvailableLayers[i].GetName()[0]);
	}

	VkApplicationInfo ApplicationInfo = VkApplicationInfo();
	ApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	ApplicationInfo.apiVersion = VK_API_VERSION_1_0;
	ApplicationInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
	ApplicationInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
	ApplicationInfo.pApplicationName = (const char*)u8"Elysium Graphics Application";
	ApplicationInfo.pEngineName = (const char*)u8"Elysium Graphics";
	ApplicationInfo.pNext = nullptr;

	VkInstanceCreateInfo InstanceCreateInfo = VkInstanceCreateInfo();
	InstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	InstanceCreateInfo.pApplicationInfo = &ApplicationInfo;
	InstanceCreateInfo.enabledExtensionCount = ExtensionPropertyNames.GetCount();
	InstanceCreateInfo.enabledLayerCount = LayerNames.GetCount();
	if (InstanceCreateInfo.enabledExtensionCount > 0)
	{
		InstanceCreateInfo.ppEnabledExtensionNames = &ExtensionPropertyNames[0];
	}
	if (InstanceCreateInfo.enabledLayerCount > 0)
	{
		InstanceCreateInfo.ppEnabledLayerNames = &LayerNames[0];
	}

	VkResult Result;
	VkInstance NativeInstanceHandle;
	if ((Result = vkCreateInstance(&InstanceCreateInfo, nullptr, &NativeInstanceHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	return NativeInstanceHandle;
}

Elysium::Core::Collections::Template::Array<Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk> Elysium::Graphics::Rendering::Vulkan::GraphicsInstanceVk::RetrievePhysicalGraphicsDevices()
{
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

VKAPI_ATTR VkBool32 VKAPI_CALL Elysium::Graphics::Rendering::Vulkan::GraphicsInstanceVk::DebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT MessageSeverity, VkDebugUtilsMessageTypeFlagsEXT MessageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	switch (MessageSeverity)
	{
	case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
		OutputDebugStringA("Vulkan VERBOSE: ");
		break;
	case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
		OutputDebugStringA("Vulkan INFO: ");
		break;
	case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
		OutputDebugStringA("Vulkan WARNING: ");
		break;
	case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
		OutputDebugStringA("Vulkan ERROR: ");
		break;
	default:
		// ToDo: throw specific exception
		throw 1;
	}
	OutputDebugStringA(pCallbackData->pMessage);
	OutputDebugStringA("\r\n");
#elif defined(ELYSIUM_CORE_OS_ANDROID)

#elif defined(ELYSIUM_CORE_OS_LINUX)

#elif defined(ELYSIUM_CORE_OS_MAC)

#else
#error "unsupported os"
#endif
	return VK_FALSE;
}
