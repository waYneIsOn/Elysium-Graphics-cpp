#include "PresentationParametersVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSINSTANCEVK
#include "GraphicsInstanceVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::PresentationParametersVk(GraphicsInstanceVk& NativeGraphicsAPI, Presentation::Control& Canvas)
	: Elysium::Graphics::PresentationParameters(NativeGraphicsAPI, Canvas)
{ }

Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::~PresentationParametersVk()
{ }

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::AddDeviceExtensionProperty(const ExtensionPropertyVk& ExtensionProperty)
{
	_DeviceExtensionPropertyNames.PushBack(const_cast<char*>(reinterpret_cast<const char*>(&ExtensionProperty.GetName()[0])));
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::ClearDeviceExtensionProperties()
{
	_DeviceExtensionPropertyNames.Clear();
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::AddDeviceQueueCreateInfo(DeviceQueueCreateInfoVk&& CreateInfo)
{
	_DeviceQueueCreateInfos.PushBack(CreateInfo);
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::ClearDeviceQueueCreateInfo()
{
	_DeviceQueueCreateInfos.Clear();
}
