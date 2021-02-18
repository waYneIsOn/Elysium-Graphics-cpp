#include "PhysicalDeviceDX12.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_EXCEPTIONDX12
#include "ExceptionDX12.hpp"
#endif

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
		_NativeAdapter = nullptr;
	}
}

const Elysium::Core::String Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12::GetName() const
{
	const Elysium::Core::Text::Encoding& UTF16LEEncoding = Elysium::Core::Text::Encoding::UTF16LE();
	return UTF16LEEncoding.GetString((Elysium::Core::byte*)&_NativeAdapterDescription.Description, std::char_traits<wchar_t>::length(_NativeAdapterDescription.Description) * sizeof(wchar_t));
}

const Elysium::Graphics::Rendering::PhysicalDeviceType Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12::GetDeviceType() const
{
	throw 1;
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

Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12::PhysicalDeviceDX12()
	: _Factory(nullptr), _NativeAdapter(nullptr), _NativeAdapterDescription()
{ }

void Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12::SetNativeAdapter(IDXGIAdapter1* NativeAdapter)
{
	_NativeAdapter = NativeAdapter;
	long Result;
	if (FAILED((Result = _NativeAdapter->GetDesc1(&_NativeAdapterDescription))))
	{
		throw ExceptionDX12(Result);
	}
}
