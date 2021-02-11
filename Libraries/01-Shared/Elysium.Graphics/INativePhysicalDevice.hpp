/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEPHYSICALDEVICE
#define ELYSIUM_GRAPHICS_RENDERING_INATIVEPHYSICALDEVICE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DEVICEQUEUECREATINFOS
#include "DeviceQueueCreateInfos.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVELOGICALDEVICE
#include "INativeLogicalDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_PHYSICALDEVICETYPE
#include "PhysicalDeviceType.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_PRESENTATIONPARAMETERS
#include "PresentationParameters.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	// Represents a specialized hardware device designed to accelerate the creation and manipulation of images - a gpu.
	class ELYSIUM_GRAPHICS_API INativePhysicalDevice
	{
	public:
		virtual ~INativePhysicalDevice() { }

		virtual const Elysium::Core::String GetName() const = 0;

		virtual const PhysicalDeviceType GetDeviceType() const = 0;

		//virtual ILogicalDevice& CreateLogicalDevice(const PresentationParameters& PresentationParameters, const DeviceQueueCreateInfos& QueueCreateInfo) = 0;
	};
}
#endif
