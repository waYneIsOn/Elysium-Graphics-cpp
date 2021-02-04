/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_PLATFORM_CANVAS
#define ELYSIUM_GRAPHICS_PLATFORM_CANVAS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EVENT
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Event.hpp"
#endif

#ifndef ELYSIUM_CORE_EVENTARGS
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/EventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_GEOMETRY_RECTANGLE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Math/Rectangle.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_DISPLAYORIENTATION
#include "DisplayOrientation.hpp"
#endif

namespace Elysium::Graphics
{
	class Game;
}

namespace Elysium::Graphics::Platform
{
	class ELYSIUM_GRAPHICS_API Canvas
	{
		friend class Game;
	public:
		Canvas(const Canvas& Source) = delete;
		Canvas(Canvas&& Right) noexcept = delete;
		virtual ~Canvas();

		Canvas& operator=(const Canvas& Source) = delete;
		Canvas& operator=(Canvas&& Right) noexcept = delete;

		virtual const Core::Math::Geometry::Rectangle& GetClientBounds() const = 0;
		virtual void* GetHandle() const = 0;
		virtual const DisplayOrientation GetDisplayOrientation() const = 0;
		virtual const Core::String& GetTitle() const = 0;

		virtual void SetTitle(const Core::String& Value) = 0;

		virtual void Show() = 0;
		virtual void Close() = 0;
	protected:
		Canvas();
		
		Core::Event<void, void*, const Core::EventArgs&> Activated;
		Core::Event<void, void*, const Core::EventArgs&> Deactivated;
		Core::Event<void, void*, const Core::EventArgs&> Suspend;
		Core::Event<void, void*, const Core::EventArgs&> Resume;
		Core::Event<void, void*, const Core::EventArgs&> SizeChanged;
		Core::Event<void, void*, const Core::EventArgs&> OrientationChanged;
		Core::Event<void, void*, const Core::EventArgs&> Idle;
		Core::Event<void, void*, const Core::EventArgs&> Paint;
		Core::Event<void, void*, const Core::EventArgs&> Exiting;
	};
}
#endif
