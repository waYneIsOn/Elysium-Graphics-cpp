#include "GraphicsInstanceDX12.hpp"

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_APINOTAVAILABLEEXCEPTION
#include "../Elysium.Graphics/APINotAvailableException.hpp"
#endif

Elysium::Graphics::Rendering::DirectX12::GraphicsInstanceDX12::GraphicsInstanceDX12()
	: _Factory(nullptr)
{ }
Elysium::Graphics::Rendering::DirectX12::GraphicsInstanceDX12::~GraphicsInstanceDX12()
{ }

const Elysium::Core::Collections::Template::Array<Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12> Elysium::Graphics::Rendering::DirectX12::GraphicsInstanceDX12::GetPhysicalGraphicsDevices()
{
	if (_Factory == nullptr)
	{
		throw Elysium::Core::InvalidOperationException(u8"Physical graphics devices can only be retrieved after initialization.");
	}

	Elysium::Core::uint32_t DeviceCount = 0;
	IDXGIAdapter1* _Adapter;
	for (Elysium::Core::uint32_t i = 0; _Factory->EnumAdapters1(i, &_Adapter) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		DeviceCount++;
	}

	Elysium::Core::Collections::Template::Array<PhysicalDeviceDX12> Devices =
		Elysium::Core::Collections::Template::Array<PhysicalDeviceDX12>(DeviceCount);
	for (Elysium::Core::uint32_t i = 0; _Factory->EnumAdapters1(i, &_Adapter) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		_Adapter->GetDesc1(&Devices[i]._NativeAdapter);
	}

	return Devices;
}

void Elysium::Graphics::Rendering::DirectX12::GraphicsInstanceDX12::Initialize(const Elysium::Graphics::Rendering::DirectX12::PresentationParametersDX12& PresentationParameters)
{
	long Result;

	//Elysium::Core::uint32_t Flags = 0;
	Elysium::Core::uint32_t Flags = DXGI_CREATE_FACTORY_DEBUG;
	if (FAILED(Result = CreateDXGIFactory2(Flags, IID_PPV_ARGS(&_Factory))))
	{
		throw APINotAvailableException();
	}
}
