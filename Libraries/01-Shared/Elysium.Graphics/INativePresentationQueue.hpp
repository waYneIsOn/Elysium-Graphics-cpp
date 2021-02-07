/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEPRESENTATIONQUEUE
#define ELYSIUM_GRAPHICS_RENDERING_INATIVEPRESENTATIONQUEUE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
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
	class ELYSIUM_GRAPHICS_API INativePresentationQueue : public INativeQueue
	{
	public:
		virtual ~INativePresentationQueue() { }

		virtual void PresentFrame(const Core::Collections::Template::Array<INativeSwapchain*>& Swapchains, const Core::Collections::Template::Array<INativeSemaphore*>& WaitSemaphores) = 0;
	};
}
#endif
