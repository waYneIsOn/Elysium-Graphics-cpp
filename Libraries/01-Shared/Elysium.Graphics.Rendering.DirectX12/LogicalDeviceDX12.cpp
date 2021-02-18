#include "LogicalDeviceDX12.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_EXCEPTIONDX12
#include "ExceptionDX12.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_PHYSICALDEVICEDX12
#include "PhysicalDeviceDX12.hpp"
#endif

Elysium::Graphics::Rendering::DirectX12::LogicalDeviceDX12::LogicalDeviceDX12(const PhysicalDeviceDX12& PhysicalDevice, Elysium::Graphics::Rendering::DirectX12::PresentationParametersDX12& PresentationParameters)
	: _PhysicalDevice(PhysicalDevice), _PresentationParameters(PresentationParameters), _Factory(PhysicalDevice._Factory), _NativeDevice(nullptr)
{
	// ToDo: D3D_FEATURE_LEVEL
	long Result;
	if (FAILED((Result = D3D12CreateDevice(_PhysicalDevice._NativeAdapter, D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&_NativeDevice)))))
	{
		throw ExceptionDX12(Result);
	}
}
Elysium::Graphics::Rendering::DirectX12::LogicalDeviceDX12::~LogicalDeviceDX12()
{
	if (_NativeDevice != nullptr)
	{
		_NativeDevice->Release();
		_NativeDevice = nullptr;
	}
}

const Elysium::Graphics::Rendering::INativePhysicalDevice& Elysium::Graphics::Rendering::DirectX12::LogicalDeviceDX12::GetPhysicalDevice() const
{
	return _PhysicalDevice;
}

Elysium::Graphics::Rendering::DirectX12::PresentationParametersDX12& Elysium::Graphics::Rendering::DirectX12::LogicalDeviceDX12::GetPresentationParameters() const
{
	return _PresentationParameters;
}

void Elysium::Graphics::Rendering::DirectX12::LogicalDeviceDX12::Wait() const
{
	// ToDo: wait for all queues
	throw 1;
}
