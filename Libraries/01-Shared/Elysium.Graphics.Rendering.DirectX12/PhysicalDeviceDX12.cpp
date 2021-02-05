#include "PhysicalDeviceDX12.hpp"

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef _TYPEINFO_
#include <typeinfo>
#endif

#ifndef _XSTRING_
#include <xstring>	// std::char_traits
#endif

Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12::~PhysicalDeviceDX12()
{
	if (_NativeAdapter != nullptr)
	{
		_NativeAdapter->Release();
	}
}

const Elysium::Core::String Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12::GetName() const
{
	const Elysium::Core::Text::Encoding& UTF16LEEncoding = Elysium::Core::Text::Encoding::UTF16LE();
	return UTF16LEEncoding.GetString((Elysium::Core::byte*)&_NativeAdapterDescription.Description, std::char_traits<wchar_t>::length(_NativeAdapterDescription.Description) * sizeof(wchar_t));
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12::GetVendorId() const
{
	return _NativeAdapterDescription.VendorId;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12::GetDeviceId() const
{
	return _NativeAdapterDescription.DeviceId;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12::GetSubSysId() const
{
	return _NativeAdapterDescription.SubSysId;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12::GetRevision() const
{
	return _NativeAdapterDescription.Revision;
}

const size_t Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12::GetDedicatedVideoMemory() const
{
	return _NativeAdapterDescription.DedicatedVideoMemory;
}

const size_t Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12::GetDedicatedSystemMemory() const
{
	return _NativeAdapterDescription.DedicatedSystemMemory;
}

const size_t Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12::GetSharedSystemMemory() const
{
	return _NativeAdapterDescription.SharedSystemMemory;
}

Elysium::Graphics::Rendering::DirectX12::LogicalDeviceDX12 Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12::CreateLogicalDevice(const PresentationParametersDX12& PresentationParameters)
{
	ID3D12Device6* NativeDevice;
	if (FAILED(D3D12CreateDevice(_NativeAdapter, D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&NativeDevice))))
	{	// ToDo: throw specific exception
		throw 1;
	}






	D3D12_COMMAND_QUEUE_DESC QueueCreationInfo = D3D12_COMMAND_QUEUE_DESC();
	QueueCreationInfo.Type = D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT;
	QueueCreationInfo.Flags = D3D12_COMMAND_QUEUE_FLAGS::D3D12_COMMAND_QUEUE_FLAG_NONE;
	QueueCreationInfo.Priority = D3D12_COMMAND_QUEUE_PRIORITY::D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	QueueCreationInfo.NodeMask = 0;

	ID3D12CommandQueue* NativeQueue;
	if (FAILED(NativeDevice->CreateCommandQueue(&QueueCreationInfo, IID_PPV_ARGS(&NativeQueue))))
	{	// ToDo: throw specific exception
		throw 1;
	}

	Elysium::Core::Collections::Template::Array<QueueDX12> Queues =
		Elysium::Core::Collections::Template::Array<QueueDX12>(0);






	return LogicalDeviceDX12(NativeDevice, std::move(Queues));
}

Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12::PhysicalDeviceDX12()
	: _NativeAdapter(nullptr), _NativeAdapterDescription()
{ }

void Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12::SetNativeAdapter(IDXGIAdapter1* NativeAdapter)
{
	_NativeAdapter = NativeAdapter;
	if (FAILED(_NativeAdapter->GetDesc1(&_NativeAdapterDescription)))
	{	// ToDo: throw specific exception
		throw 1;
	}
}
