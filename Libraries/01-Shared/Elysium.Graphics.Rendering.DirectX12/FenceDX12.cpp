#include "FenceDX12.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_EXCEPTIONDX12
#include "ExceptionDX12.hpp"
#endif

Elysium::Graphics::Rendering::DirectX12::FenceDX12::FenceDX12(const LogicalDeviceDX12& LogicalDevice, const bool SetSignaled)
	: _LogicalDevice(LogicalDevice), _NativeFence(nullptr)
{
	long Result;
	if (FAILED(Result = _LogicalDevice._NativeDevice->CreateFence(0, D3D12_FENCE_FLAGS::D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_NativeFence))))
	{
		throw ExceptionDX12(Result);
	}
}
Elysium::Graphics::Rendering::DirectX12::FenceDX12::~FenceDX12()
{
	if (_NativeFence != nullptr)
	{
		_NativeFence->Release();
		_NativeFence = nullptr;
	}
}

void Elysium::Graphics::Rendering::DirectX12::FenceDX12::Wait(const Elysium::Core::uint64_t Timeout) const
{
	throw 1;
}

void Elysium::Graphics::Rendering::DirectX12::FenceDX12::Reset()
{
	throw 1;
}
