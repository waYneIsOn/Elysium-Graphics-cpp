/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_ILOGICALDEVICE
#define ELYSIUM_GRAPHICS_RENDERING_ILOGICALDEVICE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_IQUEUE
#include "IQueue.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_ISWAPCHAIN
#include "ISwapchain.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API ILogicalDevice
	{
	public:
		virtual ~ILogicalDevice() { }

		virtual IQueue& RetrieveQueue(const Elysium::Core::uint32_t FamilyIndex, const Elysium::Core::uint32_t Index) = 0;
	};
}
#endif
