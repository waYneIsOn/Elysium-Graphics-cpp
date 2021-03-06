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

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATIONPARAMETERS
#include "PresentationParameters.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEPHYSICALDEVICE
#include "INativePhysicalDevice.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	// Represents a high level abstraction of a physical device.
	class ELYSIUM_GRAPHICS_API INativeLogicalDevice
	{
	public:
		virtual ~INativeLogicalDevice() { }

		// Return the physical device asssociated with this logical device.
		virtual const INativePhysicalDevice& GetPhysicalDevice() const = 0;

		// Returns the presentation parameters associated with this logical device.
		virtual PresentationParameters& GetPresentationParameters() const = 0;

		// Wait for the completion of outstanding operations for all queues on this logical device.
		virtual void Wait() const = 0;
	};
}
#endif
