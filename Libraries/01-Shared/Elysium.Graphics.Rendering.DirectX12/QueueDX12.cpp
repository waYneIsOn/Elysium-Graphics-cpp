#include "QueueDX12.hpp"

Elysium::Graphics::Rendering::DirectX12::QueueDX12::~QueueDX12()
{
	if (_NativeQueue != nullptr)
	{
		_NativeQueue->Release();
	}
}

Elysium::Graphics::Rendering::DirectX12::QueueDX12::QueueDX12()
	: _NativeQueue(nullptr), _NativeType(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT), _Index(-1)
{ }
