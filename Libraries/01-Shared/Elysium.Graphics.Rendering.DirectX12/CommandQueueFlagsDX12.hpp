/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_COMMANDQUEUEFLAGSDX12
#define ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_COMMANDQUEUEFLAGSDX12

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Rendering::DirectX12
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class CommandQueueFlagsDX12 : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class CommandQueueFlagsDX12
#else
#error "undefined os"
#endif
	{
		None = 0,
		DisableGPUTimeout = 0x1
	};
}
#endif
