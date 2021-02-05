#include "QueueDX12.hpp"

Elysium::Graphics::Rendering::DirectX12::QueueDX12::~QueueDX12()
{
	if (_NativeQueue != nullptr)
	{
		_NativeQueue->Release();
	}
}

Elysium::Graphics::Rendering::DirectX12::QueueDX12::QueueDX12()
	: _NativeQueue(nullptr)
{ }
