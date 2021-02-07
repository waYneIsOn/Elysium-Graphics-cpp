/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVELOGICALDEVICE
#define ELYSIUM_GRAPHICS_RENDERING_INATIVELOGICALDEVICE

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

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEQUEUE
#include "INativeQueue.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVESEMAPHORE
#include "INativeSemaphore.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVESWAPCHAIN
#include "INativeSwapchain.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API INativeLogicalDevice
	{
	public:
		virtual ~INativeLogicalDevice() { }

		virtual INativeFence& RetrieveFence() = 0;
		virtual INativeSemaphore& RetrieveSemaphore() = 0;
		virtual INativeQueue& RetrieveQueue(const Elysium::Core::uint32_t FamilyIndex, const Elysium::Core::uint32_t Index) = 0;

		virtual void Wait() = 0;
	};
}
#endif
