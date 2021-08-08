/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEQUEUE
#define ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEQUEUE

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

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVECOMMANDPOOL
#include "INativeCommandPool.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEFENCE
#include "INativeFence.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVESEMAPHORE
#include "INativeSemaphore.hpp"
#endif

namespace Elysium::Graphics::Rendering::Native
{
	// Represents...
	class ELYSIUM_GRAPHICS_API INativeQueue
	{
	public:
		virtual ~INativeQueue() { }

		virtual const Elysium::Core::uint32_t GetFamilyIndex() const = 0;

		// ToDo!!!!!
		virtual INativeCommandPool* CreateCommandPool() = 0;
		
		virtual void Submit(const INativeCommandBuffer& CommmandBuffer, const INativeSemaphore& PresentSemaphore, const INativeSemaphore& RenderSemaphore, const INativeFence& Fence) = 0;
		virtual void Wait() const = 0;
	};
}
#endif
