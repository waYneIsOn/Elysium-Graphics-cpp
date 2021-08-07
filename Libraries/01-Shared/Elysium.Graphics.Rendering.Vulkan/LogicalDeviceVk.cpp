#include "LogicalDeviceVk.hpp"

#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/ArgumentException.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_EXCEPTIONVK
#include "ExceptionVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICEVK
#include "PhysicalDeviceVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::LogicalDeviceVk(const PhysicalDeviceVk& PhysicalDevice, PresentationParametersVk& PresentationParameters)
	: _PhysicalDevice(PhysicalDevice), _PresentationParameters(PresentationParameters), _NativeLogicalDeviceHandle(VK_NULL_HANDLE)
{
	const size_t QueueCount = PresentationParameters._DeviceQueueCreateInfos.GetCount();
	if (QueueCount == 0)
	{
		throw Elysium::Core::InvalidOperationException(u8"Request at least one queue.");
	}

	Elysium::Core::Collections::Template::Array<VkDeviceQueueCreateInfo> QueueCreateInfos =
		Elysium::Core::Collections::Template::Array<VkDeviceQueueCreateInfo>(QueueCount);
	Elysium::Core::uint32_t TotalQueueCount = 0;
	for (size_t i = 0; i < QueueCount; i++)
	{
		const Elysium::Core::Collections::Template::List<float>& Priorities = PresentationParameters._DeviceQueueCreateInfos[i].GetPriorities();

		QueueCreateInfos[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		QueueCreateInfos[i].queueFamilyIndex = PresentationParameters._DeviceQueueCreateInfos[i].GetFamilyIndex();
		QueueCreateInfos[i].queueCount = Priorities.GetCount();
		QueueCreateInfos[i].pQueuePriorities = &Priorities[0];
		QueueCreateInfos[i].pNext = nullptr;
		QueueCreateInfos[i].flags = 0;

		TotalQueueCount += Priorities.GetCount();
	}

	VkDeviceCreateInfo DeviceCreateInfo = VkDeviceCreateInfo();
	DeviceCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	DeviceCreateInfo.pQueueCreateInfos = &QueueCreateInfos[0];
	DeviceCreateInfo.queueCreateInfoCount = QueueCount;
	DeviceCreateInfo.pEnabledFeatures = &PhysicalDevice._Features._NativeFeatures;
	if (PresentationParameters._DeviceExtensionPropertyNames.GetCount() > 0)
	{
		DeviceCreateInfo.ppEnabledExtensionNames = &PresentationParameters._DeviceExtensionPropertyNames[0];
		DeviceCreateInfo.enabledExtensionCount = PresentationParameters._DeviceExtensionPropertyNames.GetCount();
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
	if ((Result = vkCreateDevice(PhysicalDevice._NativePhysicalDeviceHandle, &DeviceCreateInfo, nullptr, &_NativeLogicalDeviceHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}
Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::~LogicalDeviceVk()
{
	if (_NativeLogicalDeviceHandle != VK_NULL_HANDLE)
	{
		vkDestroyDevice(_NativeLogicalDeviceHandle, nullptr);
		_NativeLogicalDeviceHandle = VK_NULL_HANDLE;
	}
}

Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk& Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::GetPresentationParameters() const
{
	return _PresentationParameters;
}

void Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::Wait() const
{
	VkResult Result;
	if ((Result = vkDeviceWaitIdle(_NativeLogicalDeviceHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}
