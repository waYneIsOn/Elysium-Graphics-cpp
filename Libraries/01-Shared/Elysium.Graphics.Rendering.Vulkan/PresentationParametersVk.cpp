#include "PresentationParametersVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSINSTANCEVK
#include "GraphicsInstanceVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::PresentationParametersVk(GraphicsInstanceVk& NativeGraphicsAPI, Presentation::Control& Canvas)
	: Elysium::Graphics::PresentationParameters(NativeGraphicsAPI, Canvas)
{ }
Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::~PresentationParametersVk()
{ }

const void* Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::GetSurfaceHandle() const
{
	return _SurfaceHandle;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::GetGraphicsQueueFamilyIndex() const
{
	return _GraphicsQueueFamilyIndex;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::GetPresentationQueueFamilyIndex() const
{
	return _PresentationQueueFamilyIndex;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::GetImageArrayLayers() const
{
	return _ImageArrayLayers;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::GetTransform() const
{
	return _Transform;
}

const Elysium::Graphics::Rendering::Vulkan::Extent2DVk& Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::GetExtent() const
{
	return _Extent;
}

const Elysium::Graphics::Rendering::Vulkan::SurfaceFormatVk& Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::GetSurfaceFormat() const
{
	return _SurfaceFormat;
}

const Elysium::Graphics::Rendering::Vulkan::PresentModeVk& Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::GetPresentMode() const
{
	return _PresentMode;
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::SetExtent(const Elysium::Core::uint32_t Width, const Elysium::Core::uint32_t Height)
{
	_Extent.Width = Width;
	_Extent.Height = Height;
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::SetSurfaceHandle(const SurfaceVk& Value)
{
	_SurfaceHandle = (void*)Value._NativeSurfaceHandle;
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::SetGraphicsQueueFamilyIndex(const Elysium::Core::uint32_t Value)
{
	_GraphicsQueueFamilyIndex = Value;
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::SetPresentationQueueFamilyIndex(const Elysium::Core::uint32_t Value)
{
	_PresentationQueueFamilyIndex = Value;
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::SetImageArrayLayers(const Elysium::Core::uint32_t Value)
{
	_ImageArrayLayers = Value;
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::SetTransform(const Elysium::Core::uint32_t Value)
{
	_Transform = Value;
}

void Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk::SetSurfaceFormat(const SurfaceFormatVk& Value)
{
	_SurfaceFormat.ColorSpace = Value.ColorSpace;
	_SurfaceFormat.Format = Value.Format;
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
