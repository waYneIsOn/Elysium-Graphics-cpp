/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_PRESENTATIONPARAMETERS
#define ELYSIUM_GRAPHICS_PRESENTATIONPARAMETERS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_DISPLAYMODE
#include "DisplayMode.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_GRAPHICSDEVICEMANAGER
#include "GraphicsDeviceManager.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATION_CONTROL
#include "../Elysium.Graphics.Presentation/Control.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATION_MONITOR
#include "../Elysium.Graphics.Presentation/Monitor.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSAPI
#include "INativeGraphicsAPI.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEPHYSICALDEVICE
#include "INativePhysicalDevice.hpp"
#endif

namespace Elysium::Graphics
{
	class ELYSIUM_GRAPHICS_API PresentationParameters
	{
	public:
		PresentationParameters(Rendering::INativeGraphicsAPI& NativeGraphicsAPI, Presentation::Control& Canvas);
		PresentationParameters(const PresentationParameters& Source) = delete;
		PresentationParameters(PresentationParameters&& Right) noexcept = delete;
		virtual ~PresentationParameters();

		PresentationParameters& operator=(const PresentationParameters& Source) = delete;
		PresentationParameters& operator=(PresentationParameters&& Right) noexcept = delete;

		const Elysium::Graphics::DisplayMode GetDisplayMode() const;
		const Elysium::Graphics::Presentation::Monitor& GetDisplayMonitor() const;
		//const Elysium::Graphics::Rendering::INativePhysicalDevice& GetDisplayeDevice() const;
		Presentation::Control& GetCanvas() const;
		const Elysium::Core::uint32_t GetBackBufferWidth() const;
		const Elysium::Core::uint32_t GetBackBufferHeight() const;
		const Elysium::Core::uint32_t GetBackBufferCount() const;

		void SetDisplayMode(const Elysium::Graphics::DisplayMode Value);
		void SetDisplayMonitorIndex(const Elysium::Core::uint32_t Value);
		void SetDisplayDeviceIndex(const Elysium::Core::uint32_t Value);
		void SetBackBufferWidth(const Elysium::Core::uint32_t Value);
		void SetBackBufferHeight(const Elysium::Core::uint32_t Value);
		void SetBackBufferCount(const Elysium::Core::uint32_t Value);
		virtual void SetExtent(const Elysium::Core::uint32_t Width, const Elysium::Core::uint32_t Height) = 0;
	protected:
		// graphics api
		Rendering::INativeGraphicsAPI& _NativeGraphicsAPI;
		Presentation::Control& _Canvas;

		// display parameters
		DisplayMode _DisplayMode = DisplayMode::Windowed;
		Elysium::Core::uint32_t _MonitorIndex = 0;
		Elysium::Core::uint32_t _PhysicalDeviceIndex = 0;
		Elysium::Core::uint32_t _RenderResolution = 100;
		bool _EnableVSync = false;

		// ...
		Elysium::Core::uint32_t _BackBufferWidth = GraphicsDeviceManager::DefaultBackBufferWidth;
		Elysium::Core::uint32_t _BackBufferHeight = GraphicsDeviceManager::DefaultBackBufferHeight;
		Elysium::Core::uint32_t _BackBufferCount = GraphicsDeviceManager::DefaultBackBufferCount;

		// ...
		Elysium::Core::uint32_t _GameFramerateLimit = 240;
		Elysium::Core::uint32_t _MenuFramerateLimit = 60;
	};
}
#endif
