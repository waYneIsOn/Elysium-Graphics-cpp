/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEFENCE
#define ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEFENCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Rendering::Native
{
	/// <summary>
	/// Fences are a synchronization primitive that can be used to insert a dependency from a queue to the host (ie. between gpu and cpu).
	/// </summary>
	class ELYSIUM_GRAPHICS_API INativeFence
	{
	public:
		virtual ~INativeFence() { }

		virtual void Wait(const Elysium::Core::uint64_t Timeout) const = 0;
		virtual void Reset() = 0;
	};
}
#endif
