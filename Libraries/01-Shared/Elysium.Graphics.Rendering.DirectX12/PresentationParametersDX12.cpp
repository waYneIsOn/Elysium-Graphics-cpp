#include "PresentationParametersDX12.hpp"

Elysium::Graphics::Rendering::DirectX12::PresentationParametersDX12::PresentationParametersDX12(Platform::Canvas& Canvas)
	: Elysium::Graphics::Rendering::PresentationParameters(Canvas)
{ }
Elysium::Graphics::Rendering::DirectX12::PresentationParametersDX12::~PresentationParametersDX12()
{ }

void Elysium::Graphics::Rendering::DirectX12::PresentationParametersDX12::AddDeviceQueueCreateInfo(DeviceQueueCreateInfoDX12 && CreateInfo)
{
	_DeviceQueueCreateInfos.Add(std::move(CreateInfo));
}

void Elysium::Graphics::Rendering::DirectX12::PresentationParametersDX12::ClearDeviceQueueCreateInfo()
{
	_DeviceQueueCreateInfos.Clear();
}
