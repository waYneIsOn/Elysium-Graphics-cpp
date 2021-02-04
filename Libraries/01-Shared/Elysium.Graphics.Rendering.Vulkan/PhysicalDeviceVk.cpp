#include "PhysicalDeviceVk.hpp"

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk::~PhysicalDeviceVk()
{ }

const Elysium::Core::String Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk::GetName() const
{
	return (char8_t*)_Properties._NativeProperties.deviceName;
}

const Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk& Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk::GetProperties() const
{
	return _Properties;
}

const Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk& Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk::GetFeatures() const
{
	return _Features;
}

const Elysium::Core::Collections::Template::Array<Elysium::Graphics::Rendering::Vulkan::QueueFamilyPropertyVk> Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk::GetQueueFamilyProperties()
{
	VkResult Result;

	Elysium::Core::uint32_t QueueFamilyPropertiesCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(_NativePhysicalDeviceHandle, &QueueFamilyPropertiesCount, nullptr);

	if (QueueFamilyPropertiesCount == 0)
	{
		return Core::Collections::Template::Array<QueueFamilyPropertyVk>(0);
	}
	else
	{
		Elysium::Core::Collections::Template::Array<VkQueueFamilyProperties> NativeQueueFamilyProperties =
			Elysium::Core::Collections::Template::Array<VkQueueFamilyProperties>(QueueFamilyPropertiesCount);
		vkGetPhysicalDeviceQueueFamilyProperties(_NativePhysicalDeviceHandle, &QueueFamilyPropertiesCount, &NativeQueueFamilyProperties[0]);

		Elysium::Core::Collections::Template::Array<QueueFamilyPropertyVk> QueueFamilyProperties =
			Elysium::Core::Collections::Template::Array<QueueFamilyPropertyVk>(QueueFamilyPropertiesCount);
		for (size_t i = 0; i < QueueFamilyPropertiesCount; i++)
		{
			QueueFamilyProperties[i]._Index = i;
			QueueFamilyProperties[i]._NativeProperties = NativeQueueFamilyProperties[i];
		}

		return QueueFamilyProperties;
	}
}

Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk::CreateLogicalDevice(const Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk & PresentationParameters, const Elysium::Core::Collections::Template::List<DeviceQueueCreateInfoVk> & DeviceQueueCreateInfos)
{
	const size_t QueueCount = DeviceQueueCreateInfos.GetCount();
	if (QueueCount == 0)
	{
		throw Elysium::Core::InvalidOperationException(u8"Request at least one queue.");
	}
	
	Elysium::Core::Collections::Template::Array<VkDeviceQueueCreateInfo> QueueCreateInfos = 
		Elysium::Core::Collections::Template::Array<VkDeviceQueueCreateInfo>(QueueCount);
	Elysium::Core::uint32_t TotalQueueCount = 0;
	for (size_t i = 0; i < QueueCount; i++)
	{
		QueueCreateInfos[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		QueueCreateInfos[i].queueFamilyIndex = DeviceQueueCreateInfos[i].FamilyIndex;
		QueueCreateInfos[i].queueCount = DeviceQueueCreateInfos[i].Count;
		QueueCreateInfos[i].pQueuePriorities = &DeviceQueueCreateInfos[i].Priority;
		QueueCreateInfos[i].pNext = nullptr;
		QueueCreateInfos[i].flags = 0;

		TotalQueueCount += DeviceQueueCreateInfos[i].Count;
	}
	
	VkDeviceCreateInfo DeviceCreateInfo = VkDeviceCreateInfo();
	DeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	DeviceCreateInfo.pQueueCreateInfos = &QueueCreateInfos[0];
	DeviceCreateInfo.queueCreateInfoCount = QueueCount;
	DeviceCreateInfo.pEnabledFeatures = &_Features._NativeFeatures;
	/*
	// ToDo: besides extension maybe also work on layers
	DeviceCreateInfo.ppEnabledExtensionNames = &PresentationParameters._ExtensionPropertyNames[0];
	DeviceCreateInfo.enabledExtensionCount = PresentationParameters._ExtensionPropertyNames.GetCount();
	*/
	DeviceCreateInfo.ppEnabledExtensionNames = nullptr;
	DeviceCreateInfo.enabledExtensionCount = 0;
	DeviceCreateInfo.ppEnabledLayerNames = &PresentationParameters._LayerPropertyNames[0];
	DeviceCreateInfo.enabledLayerCount = PresentationParameters._LayerPropertyNames.GetCount();
	DeviceCreateInfo.pNext = nullptr;
	
	VkDevice NativeLogicalDeviceHandle;
	VkResult Result;
	if ((Result = vkCreateDevice(_NativePhysicalDeviceHandle, &DeviceCreateInfo, nullptr, &NativeLogicalDeviceHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}

	// queues have been created with the logical device so retrieve them right away to not have to store DeviceQueueCreateInfos
	Elysium::Core::Collections::Template::Array<QueueVk> Queues =
		Elysium::Core::Collections::Template::Array<QueueVk>(TotalQueueCount);
	TotalQueueCount = 0;
	for (size_t i = 0; i < QueueCount; i++)
	{
		for (Elysium::Core::uint32_t j = 0; j < DeviceQueueCreateInfos[i].Count; j++)
		{
			Queues[TotalQueueCount]._FamilyIndex = i;
			Queues[TotalQueueCount]._Index = j;
			vkGetDeviceQueue(NativeLogicalDeviceHandle, DeviceQueueCreateInfos[i].FamilyIndex, j, &Queues[TotalQueueCount++]._NativeQueueHandle);
		}
	}
	
	return LogicalDeviceVk(NativeLogicalDeviceHandle, std::move(Queues));
}

Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk::PhysicalDeviceVk()
	: _NativePhysicalDeviceHandle(VK_NULL_HANDLE), _Properties(), _Features()
{ }
