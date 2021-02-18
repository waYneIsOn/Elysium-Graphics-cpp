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

#ifndef ELYSIUM_GRAPHICS_GRAPHICSDEVICEMANAGER
#include "GraphicsDeviceManager.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATION_CONTROL
#include "../Elysium.Graphics.Presentation/Control.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_SETTINGS_DISPLAYPARAMETERS
#include "DisplayParameters.hpp"
#endif

namespace Elysium::Graphics
{
	class ELYSIUM_GRAPHICS_API PresentationParameters
	{
	public:
		PresentationParameters();
		PresentationParameters(const PresentationParameters& Source) = delete;
		PresentationParameters(PresentationParameters&& Right) noexcept = delete;
		virtual ~PresentationParameters();

		PresentationParameters& operator=(const PresentationParameters& Source) = delete;
		PresentationParameters& operator=(PresentationParameters&& Right) noexcept = delete;

		const Elysium::Graphics::DisplayMode GetDisplayMode() const;
		Presentation::Control& GetControl() const;
		const Elysium::Core::uint32_t GetBackBufferWidth() const;
		const Elysium::Core::uint32_t GetBackBufferHeight() const;
		const Elysium::Core::uint32_t GetBackBufferCount() const;

		void SetDisplayMode(const Elysium::Graphics::DisplayMode Value);
		void SetDisplayMonitor(Elysium::Graphics::Presentation::Monitor& Monitor);
		void SetDisplayDevice(Elysium::Graphics::Rendering::INativePhysicalDevice& PhysicalDevice);
		void SetControl(Presentation::Control& Control);
		void SetBackBufferWidth(const Elysium::Core::uint32_t Value);
		void SetBackBufferHeight(const Elysium::Core::uint32_t Value);
		void SetBackBufferCount(const Elysium::Core::uint32_t Value);
		virtual void SetExtent(const Elysium::Core::uint32_t Width, const Elysium::Core::uint32_t Height) = 0;
	protected:
		Settings::DisplayParameters _DisplayParameters = Settings::DisplayParameters();

		Presentation::Control* _Control = nullptr;

		Elysium::Core::uint32_t _BackBufferWidth = GraphicsDeviceManager::DefaultBackBufferWidth;
		Elysium::Core::uint32_t _BackBufferHeight = GraphicsDeviceManager::DefaultBackBufferHeight;
		Elysium::Core::uint32_t _BackBufferCount = GraphicsDeviceManager::DefaultBackBufferCount;

		Elysium::Core::uint32_t _GameFramerateLimit = 240;
		Elysium::Core::uint32_t _MenuFramerateLimit = 60;
	};
}
#endif
