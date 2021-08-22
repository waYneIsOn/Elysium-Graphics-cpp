#include "PresentationParametersVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSINSTANCEVK
#include "GraphicsInstanceVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::PresentationParametersVk(GraphicsInstanceVk& NativeGraphicsAPI, Presentation::Control& Canvas)
	: Elysium::Graphics::PresentationParameters(NativeGraphicsAPI, Canvas)
{ }
Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::~PresentationParametersVk()
{ }

const Elysium::Graphics::Rendering::Vulkan::PresentModeVk& Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::GetPresentMode() const
{
	return _PresentMode;
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::SetPresentMode(const PresentModeVk& Value)
{
	_PresentMode = Value;
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::AddDeviceExtensionProperty(const ExtensionPropertyVk& ExtensionProperty)
{
	_DeviceExtensionPropertyNames.Add((char*)&ExtensionProperty.GetName()[0]);
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::ClearDeviceExtensionProperties()
{
	_DeviceExtensionPropertyNames.Clear();
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::AddDeviceQueueCreateInfo(DeviceQueueCreateInfoVk&& CreateInfo)
{
	_DeviceQueueCreateInfos.Add(CreateInfo);
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::ClearDeviceQueueCreateInfo()
{
	_DeviceQueueCreateInfos.Clear();
}
