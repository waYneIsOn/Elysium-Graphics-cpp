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

#ifndef ELYSIUM_GRAPHICS_PRESENTATION_DISPLAYDEVICE
#include "../Elysium.Graphics.Presentation/DisplayDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSAPI
#include "INativeGraphicsAPI.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DEPTHFORMAT
#include "DepthFormat.hpp"
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
		const Elysium::Graphics::Presentation::DisplayDevice& GetDisplayDevice() const;
		const Elysium::Graphics::Rendering::INativePhysicalDevice& GetGraphicsDevice() const;
		Presentation::Control& GetCanvas() const;
		const Elysium::Core::uint32_t GetBackBufferWidth() const;
		const Elysium::Core::uint32_t GetBackBufferHeight() const;
		const Elysium::Core::uint32_t GetBackBufferCount() const;
		const Rendering::DepthFormat GetDesiredDepthFormat() const;

		void SetDisplayMode(const Elysium::Graphics::DisplayMode Value);
		void SetDisplayDeviceIndex(const Elysium::Core::uint32_t Value);
		void SetGraphicsDeviceIndex(const Elysium::Core::uint32_t Value);
		void SetBackBufferWidth(const Elysium::Core::uint32_t Value);
		void SetBackBufferHeight(const Elysium::Core::uint32_t Value);
		void SetBackBufferCount(const Elysium::Core::uint32_t Value);
		void SetDesiredDepthFormat(const Rendering::DepthFormat Value);

		virtual void SetExtent(const Elysium::Core::uint32_t Width, const Elysium::Core::uint32_t Height) = 0;
	protected:
		// graphics api
		Rendering::INativeGraphicsAPI& _NativeGraphicsAPI;
		Presentation::Control& _Canvas;

		// display parameters
		DisplayMode _DisplayMode = DisplayMode::Windowed;
		Elysium::Core::uint32_t _DisplayDeviceIndex = 0;
		Elysium::Core::uint32_t _GraphicsDeviceIndex = 0;
		Elysium::Core::uint32_t _RenderResolution = 100;
		bool _EnableVSync = false;

		// swapchain & depthbuffer related parameters
		Elysium::Core::uint32_t _BackBufferWidth = GraphicsDeviceManager::DefaultBackBufferWidth;
		Elysium::Core::uint32_t _BackBufferHeight = GraphicsDeviceManager::DefaultBackBufferHeight;
		Elysium::Core::uint32_t _BackBufferCount = GraphicsDeviceManager::DefaultBackBufferCount;
		Rendering::DepthFormat _DesiredDepthFormat = Rendering::DepthFormat::Depth32Stencil8;

		// ...
		Elysium::Core::uint32_t _GameFramerateLimit = 240;
		Elysium::Core::uint32_t _MenuFramerateLimit = 60;
	};
}
#endif
