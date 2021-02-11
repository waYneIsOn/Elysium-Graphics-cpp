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

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	// Represents...
	class ELYSIUM_GRAPHICS_API INativeQueue
	{
	public:
		virtual ~INativeQueue() { }

		virtual void Wait() const = 0;
	};
}
#endif
