/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVESEMAPHORE
#define ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVESEMAPHORE

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
	/// Semaphore are a synchronization primitive that can be used to insert a dependency between queue operations or between a queue operation and 
	/// the host (ie. between gpu and gpu).
	/// </summary>
	class ELYSIUM_GRAPHICS_API INativeSemaphore
	{
	public:
		virtual ~INativeSemaphore() { }

		virtual void Wait(const Elysium::Core::uint64_t Timeout) = 0;
	};
}
#endif
