#include "ExceptionDX12.hpp"

Elysium::Graphics::Rendering::DirectX12::ExceptionDX12::ExceptionDX12(const Elysium::Core::int32_t ErrorCode)
	: Elysium::Core::Runtime::InteropServices::ExternalException(ErrorCode)
{ }
Elysium::Graphics::Rendering::DirectX12::ExceptionDX12::~ExceptionDX12()
{ }
