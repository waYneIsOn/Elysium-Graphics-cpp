#include "PhysicalDeviceVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FORMATCONVERTERVK
#include "FormatConverterVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk::PhysicalDeviceVk()
	: _NativePhysicalDeviceHandle(VK_NULL_HANDLE), _Properties(), _Features()
{ }

Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk::~PhysicalDeviceVk()
{ }

const Elysium::Core::Utf8String Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk::GetName() const
{
	return (char8_t*)_Properties._NativeProperties.deviceName;
}

const Elysium::Graphics::Rendering::PhysicalDeviceType Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk::GetDeviceType() const
{
	return FormatConverterVk::Convert(_Properties._NativeProperties.deviceType);
}

const Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk& Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk::GetProperties() const
{
	return _Properties;
}

const Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk& Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk::GetFeatures() const
{
	return _Features;
}

const Elysium::Core::Template::Container::Vector<Elysium::Graphics::Rendering::Vulkan::QueueFamilyPropertyVk> Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk::GetQueueFamilyProperties() const
{
	VkResult Result;

	Elysium::Core::uint32_t QueueFamilyPropertiesCount;
	vkGetPhysicalDeviceQueueFamilyProperties(_NativePhysicalDeviceHandle, &QueueFamilyPropertiesCount, nullptr);

	if (QueueFamilyPropertiesCount == 0)
	{
		return Elysium::Core::Template::Container::Vector<QueueFamilyPropertyVk>(0);
	}
	else
	{
		Elysium::Core::Template::Container::Vector<VkQueueFamilyProperties> NativeQueueFamilyProperties =
			Elysium::Core::Template::Container::Vector<VkQueueFamilyProperties>(QueueFamilyPropertiesCount);
		vkGetPhysicalDeviceQueueFamilyProperties(_NativePhysicalDeviceHandle, &QueueFamilyPropertiesCount, &NativeQueueFamilyProperties[0]);

		//vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR
		//vkGetPhysicalDeviceQueueFamilyProperties2
		//vkGetPhysicalDeviceQueueFamilyProperties2KHR

		Elysium::Core::Template::Container::Vector<QueueFamilyPropertyVk> QueueFamilyProperties =
			Elysium::Core::Template::Container::Vector<QueueFamilyPropertyVk>(QueueFamilyPropertiesCount);
		for (size_t i = 0; i < QueueFamilyPropertiesCount; i++)
		{
			QueueFamilyProperties[i]._Index = i;
			QueueFamilyProperties[i]._NativeProperties = NativeQueueFamilyProperties[i];
		}

		return QueueFamilyProperties;
	}
}

const Elysium::Core::Template::Container::Vector<Elysium::Graphics::Rendering::Vulkan::ExtensionPropertyVk> Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk::GetAvailableExtensions() const
{
	VkResult Result;

	Elysium::Core::uint32_t ExtensionCount = 0;
	if ((Result = vkEnumerateDeviceExtensionProperties(_NativePhysicalDeviceHandle, nullptr, &ExtensionCount, nullptr)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	Elysium::Core::Template::Container::Vector<ExtensionPropertyVk> Extensions =
		Elysium::Core::Template::Container::Vector<ExtensionPropertyVk>(ExtensionCount);
	if ((Result = vkEnumerateDeviceExtensionProperties(_NativePhysicalDeviceHandle, nullptr, &ExtensionCount, (VkExtensionProperties*)&Extensions[0])) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	return Extensions;
}
const bool Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk::SupportsPresentation(const VkSurfaceKHR NativeSurfaceHandle, const Elysium::Core::uint32_t FamilyIndex) const
{
	Elysium::Core::uint32_t SupportsPresentation;
	vkGetPhysicalDeviceSurfaceSupportKHR(_NativePhysicalDeviceHandle, FamilyIndex, NativeSurfaceHandle, &SupportsPresentation);

	return SupportsPresentation == 1;
}
