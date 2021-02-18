/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEQUEUE
#define ELYSIUM_GRAPHICS_RENDERING_INATIVEQUEUE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEFENCE
#include "INativeFence.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVESEMAPHORE
#include "INativeSemaphore.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	// Represents...
	class ELYSIUM_GRAPHICS_API INativeQueue
	{
	public:
		virtual ~INativeQueue() { }

		virtual const Elysium::Core::uint32_t GetFamilyIndex() const = 0;
		
		virtual void Submit(const INativeSemaphore& PresentSemaphore, const INativeSemaphore& RenderSemaphore, const INativeFence& Fence) = 0;
		virtual void Wait() const = 0;
	};
}
#endif
