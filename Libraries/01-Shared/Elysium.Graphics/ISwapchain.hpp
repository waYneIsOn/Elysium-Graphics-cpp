/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_ISWAPCHAIN
#define ELYSIUM_GRAPHICS_RENDERING_ISWAPCHAIN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API ISwapchain
	{
	public:
		virtual ~ISwapchain() { }
	};
}
#endif
