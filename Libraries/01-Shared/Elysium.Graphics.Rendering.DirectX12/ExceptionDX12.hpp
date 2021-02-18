/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_EXCEPTIONDX12
#define ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_EXCEPTIONDX12

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_EXTERNALEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/ExternalException.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Rendering::DirectX12
{
	class ExceptionDX12 final : public Elysium::Core::Runtime::InteropServices::ExternalException
	{
	public:
		ExceptionDX12(const Elysium::Core::int32_t ErrorCode);
		ExceptionDX12(const ExceptionDX12& Source) = delete;
		ExceptionDX12(ExceptionDX12&& Right) noexcept = delete;
		virtual ~ExceptionDX12();

		ExceptionDX12& operator=(const ExceptionDX12& Source) = delete;
		ExceptionDX12& operator=(ExceptionDX12&& Right) noexcept = delete;
	};
}
#endif
