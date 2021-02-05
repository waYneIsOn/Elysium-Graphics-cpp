#include "LogicalDeviceDX12.hpp"

Elysium::Graphics::Rendering::DirectX12::LogicalDeviceDX12::~LogicalDeviceDX12()
{
	if (_Device != nullptr)
	{
		_Device->Release();
	}
}

Elysium::Graphics::Rendering::DirectX12::QueueDX12& Elysium::Graphics::Rendering::DirectX12::LogicalDeviceDX12::RetrieveQueue(const Elysium::Core::uint32_t FamilyIndex, const Elysium::Core::uint32_t Index)
{
	throw 1;
}

Elysium::Graphics::Rendering::DirectX12::LogicalDeviceDX12::LogicalDeviceDX12(ID3D12Device6 * Device, Elysium::Core::Collections::Template::Array<QueueDX12>&& Queues)
	: _Device(Device), _Queues(std::move(Queues))
{ }
