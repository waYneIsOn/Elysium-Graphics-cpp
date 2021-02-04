#include "PhysicalDeviceDX12.hpp"

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef _XSTRING_
#include <xstring>	// std::char_traits
#endif

Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12::~PhysicalDeviceDX12()
{ }

const Elysium::Core::String Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12::GetName() const
{
	const Elysium::Core::Text::Encoding& UTF16LEEncoding = Elysium::Core::Text::Encoding::UTF16LE();
	return UTF16LEEncoding.GetString((Elysium::Core::byte*)&_NativeAdapter.Description, std::char_traits<wchar_t>::length(_NativeAdapter.Description) * sizeof(wchar_t));
}

Elysium::Graphics::Rendering::DirectX12::PhysicalDeviceDX12::PhysicalDeviceDX12()
	: _NativeAdapter()
{ }
