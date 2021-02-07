/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEFENCE
#define ELYSIUM_GRAPHICS_RENDERING_INATIVEFENCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	// A fence is a synchronization primitive
	class ELYSIUM_GRAPHICS_API INativeFence
	{
	public:
		virtual ~INativeFence() { }

		virtual void Wait(const Elysium::Core::uint64_t Timeout) = 0;
		virtual void Reset() = 0;
	};
}
#endif
