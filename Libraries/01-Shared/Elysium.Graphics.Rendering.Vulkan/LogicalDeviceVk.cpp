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

Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::LogicalDeviceVk(const PhysicalDeviceVk& PhysicalDevice, const SurfaceVk& Surface, PresentationParametersVk& PresentationParameters)
	: _PhysicalDevice(PhysicalDevice), _Surface(Surface), _PresentationParameters(PresentationParameters), 
	_NativeLogicalDeviceHandle(CreateNativeLogicalDeviceHandle())
{ }
Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::~LogicalDeviceVk()
{
	if (_NativeLogicalDeviceHandle != VK_NULL_HANDLE)
	{
		vkDestroyDevice(_NativeLogicalDeviceHandle, nullptr);
	}
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::GetGraphicsQueueFamilyIndex() const
{
	return _GraphicsQueueFamilyIndex;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::GetPresentationQueueFamilyIndex() const
{
	return _PresentationQueueFamilyIndex;
}

void Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::Wait() const
{
	VkResult Result;
	if ((Result = vkDeviceWaitIdle(_NativeLogicalDeviceHandle)) != VK_SUCCESS)
	{
		throw ExceptionVk(Result);
	}
}

const VkDevice Elysium::Graphics::Rendering::Vulkan::LogicalDeviceVk::CreateNativeLogicalDeviceHandle()
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
			if (_GraphicsQueueFamilyIndex == -1)
			{
				_GraphicsQueueFamilyIndex = i;
			}
			if (_PresentationQueueFamilyIndex == -1)
			{
				if (_PhysicalDevice.SupportsPresentation(_Surface._NativeSurfaceHandle, i))
				{
					_PresentationQueueFamilyIndex = i;
				}
			}

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
