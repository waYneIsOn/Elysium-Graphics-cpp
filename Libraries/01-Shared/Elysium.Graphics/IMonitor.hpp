/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_PLATFORM_IMONITOR
#define ELYSIUM_GRAPHICS_PLATFORM_IMONITOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_GEOMETRY_POINT
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Math/Point.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Platform
{
	class ELYSIUM_GRAPHICS_API IMonitor 
	{
	public:
		virtual ~IMonitor() { }

		// ...
		virtual const void* GetHandle() const = 0;

		// ...
		virtual const bool GetIsPrimaryMonitor() const = 0;

		// ...
		virtual const Elysium::Core::String GetName() const = 0;

		// Gets the physical size of the monitor in millimetres.
		virtual const Elysium::Core::Math::Geometry::Point& GetPhysicalSize() const = 0;

		// ...
		virtual const Elysium::Core::Math::Geometry::Point& GetCurrentResolution() const = 0;

		// ...
		virtual const Elysium::Core::uint32_t GetCurrentRefreshRate() const = 0;

		// ...
		virtual const Elysium::Core::Math::Geometry::Point& GetPosition() const = 0;
	};
}
#endif
