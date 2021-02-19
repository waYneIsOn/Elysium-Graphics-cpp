/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSDEVICE
#define ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSDEVICE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATIONPARAMETERS
#include "PresentationParameters.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSAPI
#include "INativeGraphicsAPI.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEPHYSICALDEVICE
#include "INativePhysicalDevice.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API INativeGraphicsDevice
	{
	public:
		virtual ~INativeGraphicsDevice() { }

		virtual const INativeGraphicsAPI& GetGraphicsAPI() const = 0;
		virtual const PresentationParameters& GetPresentationParameters() const = 0;
		virtual const INativePhysicalDevice& GetPhysicalDevice() const = 0;
	};
}
#endif
