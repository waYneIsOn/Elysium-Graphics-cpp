#include "LogicalDeviceDX12.hpp"

Elysium::Graphics::Rendering::DirectX12::LogicalDeviceDX12::~LogicalDeviceDX12()
{
	if (_Device != nullptr)
	{
		_Device->Release();
	}
}

Elysium::Graphics::Rendering::DirectX12::SwapchainDX12 Elysium::Graphics::Rendering::DirectX12::LogicalDeviceDX12::CreateSwapchain(const PresentationParametersDX12& PresentationParameter)
{
	//_Factory->CreateSwapChainForHwnd()

	throw 1;
}

Elysium::Graphics::Rendering::DirectX12::QueueDX12& Elysium::Graphics::Rendering::DirectX12::LogicalDeviceDX12::RetrieveQueue(const Elysium::Core::uint32_t FamilyIndex, const Elysium::Core::uint32_t Index)
{
	const Elysium::Graphics::Rendering::DirectX12::QueueDX12& Result = _Queues[FamilyIndex];
	if (Result._NativeType != FamilyIndex)
	{	// ToDo: throw specific exception
		throw 1;
	}
	return _Queues[FamilyIndex];
}

Elysium::Graphics::Rendering::DirectX12::LogicalDeviceDX12::LogicalDeviceDX12(IDXGIFactory2* Factory, ID3D12Device6 * Device, Elysium::Core::Collections::Template::Array<QueueDX12>&& Queues)
	: _Factory(Factory), _Device(Device), _Queues(std::move(Queues))
{ }
