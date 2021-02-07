/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_COMMANDQUEUEPRIORITYDX12
#define ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_COMMANDQUEUEPRIORITYDX12

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
	enum class CommandQueuePriorityDX12 : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class CommandQueuePriorityDX12
#else
#error "undefined os"
#endif
	{
		Normal = 0,
		High = 100,
		GlobalRealtime = 10000
	};
}
#endif
