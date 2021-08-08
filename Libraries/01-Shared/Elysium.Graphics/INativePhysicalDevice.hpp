/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEPHYSICALDEVICE
#define ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEPHYSICALDEVICE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_PHYSICALDEVICETYPE
#include "PhysicalDeviceType.hpp"
#endif

namespace Elysium::Graphics::Rendering::Native
{
	// Represents a specialized hardware device designed to accelerate the creation and manipulation of images - a gpu.
	class ELYSIUM_GRAPHICS_API INativePhysicalDevice
	{
	public:
		virtual ~INativePhysicalDevice() { }

		virtual const Elysium::Core::String GetName() const = 0;

		virtual const PhysicalDeviceType GetDeviceType() const = 0;
	};
}
#endif
