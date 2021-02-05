/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_IPHYSICALDEVICE
#define ELYSIUM_GRAPHICS_RENDERING_IPHYSICALDEVICE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DEVICEQUEUECREATINFOS
#include "DeviceQueueCreateInfos.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_ILOGICALDEVICE
#include "ILogicalDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_PRESENTATIONPARAMETERS
#include "PresentationParameters.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API IPhysicalDevice
	{
	public:
		virtual ~IPhysicalDevice() { }

		virtual const Elysium::Core::String GetName() const = 0;

		//virtual ILogicalDevice& CreateLogicalDevice(const PresentationParameters& PresentationParameters, const DeviceQueueCreateInfos& QueueCreateInfo) = 0;
	};
}
#endif
