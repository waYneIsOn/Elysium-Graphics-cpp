/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSAPI
#define ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSAPI

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_ARRAY
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEPHYSICALDEVICE
#include "INativePhysicalDevice.hpp"
#endif

namespace Elysium::Graphics::Rendering::Native
{
	class ELYSIUM_GRAPHICS_API INativeGraphicsAPI
	{
	public:
		virtual ~INativeGraphicsAPI() { }

		virtual const INativePhysicalDevice& GetPhysicalDevice(const Elysium::Core::uint32_t Index) const = 0;
		//virtual const Elysium::Core::Template::Container::Vector<INativePhysicalDevice> GetPhysicalGraphicsDevices() const = 0;

		virtual void EnableDebugging() = 0;
		virtual void DisableDebugging() = 0;
	};
}
#endif
