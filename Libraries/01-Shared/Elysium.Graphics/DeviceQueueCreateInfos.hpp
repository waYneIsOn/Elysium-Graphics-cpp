/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_DEVICEQUEUECREATINFOS
#define ELYSIUM_GRAPHICS_RENDERING_DEVICEQUEUECREATINFOS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API DeviceQueueCreateInfos
	{
	public:
		DeviceQueueCreateInfos();
		DeviceQueueCreateInfos(const DeviceQueueCreateInfos& Source) = delete;
		DeviceQueueCreateInfos(DeviceQueueCreateInfos&& Right) noexcept = delete;
		virtual ~DeviceQueueCreateInfos();

		DeviceQueueCreateInfos& operator=(const DeviceQueueCreateInfos& Source) = delete;
		DeviceQueueCreateInfos& operator=(DeviceQueueCreateInfos&& Right) noexcept = delete;
	protected:
	};
}
#endif
