/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_COMMANDQUEUETYPEDX12
#define ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_COMMANDQUEUETYPEDX12

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
	enum class CommandQueueTypeDX12 : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class CommandQueueTypeDX12
#else
#error "undefined os"
#endif
	{
		// Specifies a command buffer that the GPU can execute. A direct command list doesn't inherit any GPU state.
		Direct = 0,

		// Specifies a command buffer that can be executed only directly via a direct command list. 
		// A bundle command list inherits all GPU state (except for the currently set pipeline state object and primitive topology).
		Bundle = 1,

		// Specifies a command buffer for computing.
		Compute = 2,

		// Specifies a command buffer for copying.
		Copy = 3,

		// Specifies a command buffer for video decoding.
		VideoDecode = 4,

		// Specifies a command buffer for video processing.
		VideoProcess = 5,

		// Specifies a command buffer for video encoding.
		VideoEncode = 6
	};
}
#endif
