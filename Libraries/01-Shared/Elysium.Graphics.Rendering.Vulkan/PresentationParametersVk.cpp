#include "PresentationParametersVk.hpp"

Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::PresentationParametersVk(const Platform::Canvas& Canvas)
	: Elysium::Graphics::Rendering::PresentationParameters(Canvas)
{ }
Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::~PresentationParametersVk()
{ }

const Elysium::Core::String& Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::GetApplicationName() const
{
	return _ApplicationName;
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::AddInstanceExtensionProperty(const ExtensionPropertyVk& ExtensionProperty)
{
	_InstanceExtensionPropertyNames.Add((char*)&ExtensionProperty.GetName()[0]);
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::ClearInstanceExtensionProperties()
{
	_InstanceExtensionPropertyNames.Clear();
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::AddDeviceExtensionProperty(const ExtensionPropertyVk& ExtensionProperty)
{
	_DeviceExtensionPropertyNames.Add((char*)&ExtensionProperty.GetName()[0]);
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::ClearDeviceExtensionProperties()
{
	_DeviceExtensionPropertyNames.Clear();
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::AddLayerProperty(const LayerPropertyVk& LayerProperty)
{
	_LayerPropertyNames.Add((char*)&LayerProperty.GetName()[0]);
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::ClearLayerProperties()
{
	_LayerPropertyNames.Clear();
}
