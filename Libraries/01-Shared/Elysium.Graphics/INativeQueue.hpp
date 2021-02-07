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
	class ELYSIUM_GRAPHICS_API INativeQueue
	{
	public:
		virtual ~INativeQueue() { }

		virtual void Wait() = 0;
	};
}
#endif
