/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSAPI
#define ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSAPI

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_ARRAY
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif
/*
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEPHYSICALDEVICE
#include "INativePhysicalDevice.hpp"
#endif
*/
namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API INativeGraphicsAPI
	{
	public:
		virtual ~INativeGraphicsAPI() { }

		virtual void EnableDebugging() = 0;
		virtual void DisableDebugging() = 0;

		virtual void Initialize() = 0;

		//const Array<INativePhysicalDevice> GetPhysicalGraphicsDevices() const = 0;
	};
}
#endif
