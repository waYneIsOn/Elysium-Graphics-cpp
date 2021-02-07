/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVESWAPCHAIN
#define ELYSIUM_GRAPHICS_RENDERING_INATIVESWAPCHAIN

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

namespace Elysium::Graphics::Rendering
{

	// A swap chain holds a set of backbuffer images. One of those images, the screenbuffer, is rendered to the output of the video card.
	class ELYSIUM_GRAPHICS_API INativeSwapchain
	{
	public:
		virtual ~INativeSwapchain() { }

		virtual void AquireNextImage(const Elysium::Core::uint64_t Timeout, const INativeSemaphore& ImageAvailableSemaphore, const INativeFence& Fence) = 0;
		virtual void PresentFrame(const INativeQueue& PresentationQueue, const INativeSemaphore& WaitSemaphore) = 0;
	};
}
#endif
