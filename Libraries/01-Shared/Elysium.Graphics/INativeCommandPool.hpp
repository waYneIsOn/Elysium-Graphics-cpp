/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVECOMMANDPOOL
#define ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVECOMMANDPOOL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVECOMMANDBUFFER
#include "INativeCommandBuffer.hpp"
#endif

namespace Elysium::Graphics::Rendering::Native
{
	class ELYSIUM_GRAPHICS_API INativeCommandPool
	{
	public:
		virtual ~INativeCommandPool() { }

		// ToDo!!!!!
		virtual INativeCommandBuffer* CreateCommandBuffer(const bool IsPrimary) = 0;

		virtual void Reset() = 0;
	};
}
#endif
