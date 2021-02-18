#include "GraphicsInstanceDX12.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_EXCEPTIONDX12
#include "ExceptionDX12.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_APINOTAVAILABLEEXCEPTION
#include "../Elysium.Graphics/APINotAvailableException.hpp"
#endif

Elysium::Graphics::Rendering::DirectX12::GraphicsInstanceDX12::GraphicsInstanceDX12()
	: _Factory(nullptr), _Debug(nullptr)
{ }
Elysium::Graphics::Rendering::DirectX12::GraphicsInstanceDX12::~GraphicsInstanceDX12()
{
	if (_Factory != nullptr)
	{
		_Factory->Release();
		_Factory = nullptr;
	}
}

const Elysium::Core::Collections::Template::Array<Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12> Elysium::Graphics::Rendering::DirectX12::GraphicsInstanceDX12::GetPhysicalGraphicsDevices()
{
	if (_Factory == nullptr)
	{
		throw Elysium::Core::InvalidOperationException(u8"Physical graphics devices can only be retrieved after initialization.");
	}

	Elysium::Core::uint32_t DeviceCount = 0;
	IDXGIAdapter1* Adapter1;
	for (Elysium::Core::uint32_t i = 0; _Factory->EnumAdapters1(i, &Adapter1) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		DeviceCount++;
		Adapter1->Release();
	}

	Elysium::Core::Collections::Template::Array<PhysicalDeviceDX12> Devices =
		Elysium::Core::Collections::Template::Array<PhysicalDeviceDX12>(DeviceCount);
	//IDXGIAdapter4* _Adapter4;
	for (Elysium::Core::uint32_t i = 0; _Factory->EnumAdapters1(i, &Adapter1) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		Devices[i]._Factory = _Factory;

		//Adapter1->As(_Adapter4);
		Devices[i].SetNativeAdapter(Adapter1);
	}

	return Devices;
}

void Elysium::Graphics::Rendering::DirectX12::GraphicsInstanceDX12::EnableDebugging()
{
	if (_Factory == nullptr)
	{
		throw Elysium::Core::InvalidOperationException(u8"Elysium::Graphics::Rendering::DirectX12::GraphicsInstanceDX12 needs to be initialized before calling this method.");
	}

	long Result;
	if (FAILED(Result = D3D12GetDebugInterface(IID_PPV_ARGS(&_Debug))))
	{
		throw ExceptionDX12(Result);
	}

	_Debug->EnableDebugLayer();
}

void Elysium::Graphics::Rendering::DirectX12::GraphicsInstanceDX12::DisableDebugging()
{
	if (_Factory == nullptr)
	{
		throw Elysium::Core::InvalidOperationException(u8"Elysium::Graphics::Rendering::DirectX12::GraphicsInstanceDX12 needs to be initialized before calling this method.");
	}

	if (_Debug != nullptr)
	{
		_Debug->Release();
		_Debug = nullptr;
	}
}

void Elysium::Graphics::Rendering::DirectX12::GraphicsInstanceDX12::Initialize(const Elysium::Graphics::Rendering::DirectX12::PresentationParametersDX12& PresentationParameters)
{
	long Result;
	Elysium::Core::uint32_t Flags = DXGI_CREATE_FACTORY_DEBUG;
	if (FAILED(Result = CreateDXGIFactory2(Flags, IID_PPV_ARGS(&_Factory))))
	{
		throw APINotAvailableException();
	}
}
