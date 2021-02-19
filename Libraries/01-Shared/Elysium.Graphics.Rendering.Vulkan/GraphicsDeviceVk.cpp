#include "GraphicsDeviceVk.hpp"

Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GraphicsDeviceVk(GraphicsInstanceVk& GraphicsInstance, PresentationParametersVk& PresentationParameters)
	: _GraphicsInstance(GraphicsInstance), _PresentationParameters(PresentationParameters),
	_Surface(_GraphicsInstance, PresentationParameters)
{ }
Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::~GraphicsDeviceVk()
{ }

const Elysium::Graphics::Rendering::Vulkan::GraphicsInstanceVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetGraphicsAPI() const
{
	return _GraphicsInstance;
}

const Elysium::Graphics::Rendering::Vulkan::PresentationParametersVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetPresentationParameters() const
{
	return _PresentationParameters;
}

const Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk& Elysium::Graphics::Rendering::Vulkan::GraphicsDeviceVk::GetPhysicalDevice() const
{
	throw 1;
	//return (Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceVk&)_PresentationParameters.GetDisplayeDevice();
}
