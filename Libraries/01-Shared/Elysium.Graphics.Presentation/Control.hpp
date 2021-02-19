/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_PRESENTATION_CONTROL
#define ELYSIUM_GRAPHICS_PRESENTATION_CONTROL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EVENT
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Event.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATION_API
#include "API.hpp"
#endif

namespace Elysium::Graphics::Presentation
{
	class ELYSIUM_GRAPHICS_PRESENTATION_API Control
	{
	public:
		virtual ~Control() { }

		Elysium::Core::Event<void, const Control&, const bool> ActivationChanged;
		Elysium::Core::Event<void, const Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t> SizeChanged;
		Elysium::Core::Event<void, const Control&> Paint;
		Elysium::Core::Event<void, const Control&> Exiting;

		virtual const size_t GetHandle() const = 0;

		virtual void Show() = 0;
		virtual void Close() = 0;
	};
}
#endif
