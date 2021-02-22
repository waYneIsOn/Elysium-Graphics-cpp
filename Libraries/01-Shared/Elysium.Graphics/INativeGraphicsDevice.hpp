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

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEFENCE
#include "INativeFence.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSAPI
#include "INativeGraphicsAPI.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEPHYSICALDEVICE
#include "INativePhysicalDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEQUEUE
#include "INativeQueue.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVESEMAPHORE
#include "INativeSemaphore.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API INativeGraphicsDevice
	{
	public:
		virtual ~INativeGraphicsDevice() { }

		virtual const INativeGraphicsAPI& GetGraphicsAPI() const = 0;
		virtual PresentationParameters& GetPresentationParameters() = 0;
		virtual const INativePhysicalDevice& GetPhysicalDevice() const = 0;

		virtual const INativeFence& GetRenderFence() const = 0;
		virtual const INativeSemaphore& GetPresentationSemaphore() const = 0;
		virtual const INativeSemaphore& GetRenderSemaphore() const = 0;

		virtual INativeQueue& GetGraphicsQueue() = 0;

		virtual void Wait() const = 0;
		virtual const bool BeginDraw() = 0;
		virtual void EndDraw() = 0;
	};
}
#endif
