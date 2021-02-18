/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_SETTINGS_DISPLAYPARAMETERS
#define ELYSIUM_GRAPHICS_SETTINGS_DISPLAYPARAMETERS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_DISPLAYMODE
#include "DisplayMode.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATION_MONITOR
#include "../Elysium.Graphics.Presentation/Monitor.hpp"
#endif

namespace Elysium::Graphics
{
	class PresentationParameters;

	namespace Rendering
	{
		class INativePhysicalDevice;
	}
}

namespace Elysium::Graphics::Settings
{
	class ELYSIUM_GRAPHICS_API DisplayParameters final
	{
		friend class Elysium::Graphics::PresentationParameters;
	public:
		DisplayParameters(const DisplayParameters& Source) = delete;
		DisplayParameters(DisplayParameters&& Right) noexcept = delete;
		~DisplayParameters();

		DisplayParameters& operator=(const DisplayParameters& Source) = delete;
		DisplayParameters& operator=(DisplayParameters&& Right) noexcept = delete;
	private:
		DisplayParameters();

		DisplayMode _DisplayMode = DisplayMode::Windowed;
		Elysium::Graphics::Presentation::Monitor* _SelectedMonitor = nullptr;
		Elysium::Graphics::Rendering::INativePhysicalDevice* _SelectedPhysicalDevice = nullptr;
		Elysium::Core::uint32_t _RenderResolution = 100;
		bool _EnableVSync = false;
		//Platform::IMonitor& _DisplayMonitor;
		//Rendering::IPhysicalDevice _DisplayAdapter;
	};
}
#endif
