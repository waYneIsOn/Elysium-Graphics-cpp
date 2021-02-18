#include "PresentationParametersDX12.hpp"

Elysium::Graphics::Rendering::DirectX12::PresentationParametersDX12::PresentationParametersDX12()
	: Elysium::Graphics::PresentationParameters()
{ }
Elysium::Graphics::Rendering::DirectX12::PresentationParametersDX12::~PresentationParametersDX12()
{ }

void Elysium::Graphics::Rendering::DirectX12::PresentationParametersDX12::SetExtent(const Elysium::Core::uint32_t Width, const Elysium::Core::uint32_t Height)
{
	throw 1;
}

void Elysium::Graphics::Rendering::DirectX12::PresentationParametersDX12::AddDeviceQueueCreateInfo(DeviceQueueCreateInfoDX12 && CreateInfo)
{
	_DeviceQueueCreateInfos.Add(std::move(CreateInfo));
}

void Elysium::Graphics::Rendering::DirectX12::PresentationParametersDX12::ClearDeviceQueueCreateInfo()
{
	_DeviceQueueCreateInfos.Clear();
}
